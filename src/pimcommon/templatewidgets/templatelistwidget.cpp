/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templatelistwidget.h"
#include "templateeditdialog.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <KMessageBox>
#include <KLocalizedString>
#include <QMenu>
#include <KNS3/DownloadDialog>
#include <KAuthorized>
#include <QIcon>

#include <QListWidgetItem>
#include <QPointer>
#include <QMimeData>
#include <QDropEvent>
#include <QFileDialog>

namespace PimCommon {
class TemplateListWidgetPrivate
{
public:
    TemplateListWidgetPrivate(const QString &configName, TemplateListWidget *qq)
        : config(KSharedConfig::openConfig(configName, KConfig::NoGlobals))
        , q(qq)
    {
    }

    ~TemplateListWidgetPrivate()
    {
        save();
    }

    void createListWidgetItem(const QString &name, const QString &text, bool isDefaultTemplate)
    {
        auto *item = new QListWidgetItem(name, q);
        item->setData(TemplateListWidget::Text, text);
        item->setData(TemplateListWidget::DefaultTemplate, isDefaultTemplate);
        if (isDefaultTemplate) {
            item->setIcon(QIcon::fromTheme(QStringLiteral("lock")));
        }
        q->setCurrentItem(item);
    }

    void slotAdd()
    {
        QString templateName;
        QString templateScript;
        if (q->addNewTemplate(templateName, templateScript)) {
            createListWidgetItem(templateName, templateScript, false);
            dirty = true;
        }
    }

    void slotInsertNewTemplate(const QString &newTemplateScript)
    {
        QString templateName;
        QString templateScript = newTemplateScript;
        if (q->modifyTemplate(templateName, templateScript, false)) {
            createListWidgetItem(templateName, templateScript, false);
            dirty = true;
        }
    }

    void slotRemove()
    {
        if (KMessageBox::Yes == KMessageBox::questionYesNo(q, i18n("Do you want to delete selected template?"), i18n("Delete template"))) {
            const QList<QListWidgetItem *> lstSelectedItems = q->selectedItems();
            for (QListWidgetItem *item : lstSelectedItems) {
                if (item->data(TemplateListWidget::DefaultTemplate).toBool() == false) {
                    delete item;
                }
            }
            dirty = true;
        }
    }

    void slotModify()
    {
        QListWidgetItem *item = q->currentItem();
        if (item) {
            const bool defaultTemplate = item->data(TemplateListWidget::DefaultTemplate).toBool();

            QString templateName = item->text();
            QString templateScript = item->data(TemplateListWidget::Text).toString();
            if (q->modifyTemplate(templateName, templateScript, defaultTemplate)) {
                if (!defaultTemplate) {
                    item->setText(templateName);
                    item->setData(TemplateListWidget::Text, templateScript);
                    dirty = true;
                }
            }
        }
    }

    void slotInsertTemplate()
    {
        QListWidgetItem *item = q->currentItem();
        if (item) {
            const QString templateScript = item->data(TemplateListWidget::Text).toString();
            Q_EMIT q->insertTemplate(templateScript);
        }
    }

    void slotDuplicate()
    {
        QListWidgetItem *item = q->currentItem();
        if (item) {
            QStringList name;
            name.reserve(q->count());
            for (int i = 0; i < q->count(); ++i) {
                name.append(q->item(i)->text());
            }
            QString templateName = item->text() + QLatin1String(" (%1)");
            QString newName;
            int i = 1;
            do {
                newName = templateName.arg(i);
                i++;
            } while (name.contains(newName));

            const QString templateScript = item->data(TemplateListWidget::Text).toString();
            createListWidgetItem(newName, templateScript, false);
            dirty = true;
            slotModify();
        }
    }

    void slotImportTemplates()
    {
        const QString templateFile = QFileDialog::getOpenFileName(q, i18n("Import Template"));
        if (!templateFile.isEmpty()) {
            KConfig conf(templateFile, KConfig::SimpleConfig);
            loadTemplates(&conf);
        }
    }

    void slotExportTemplates()
    {
        const QString templateFile = QFileDialog::getSaveFileName(q, i18n("Export Template"));
        if (!templateFile.isEmpty()) {
            KConfig conf(templateFile, KConfig::SimpleConfig);
            saveTemplates(&conf);
        }
    }

    void slotContextMenu(const QPoint &pos)
    {
        const QList<QListWidgetItem *> lstSelectedItems = q->selectedItems();
        const bool listSelectedIsEmpty = lstSelectedItems.isEmpty();
        auto *menu = new QMenu(q);

        if (!listSelectedIsEmpty) {
            menu->addAction(i18n("Insert template"), q, [this]() {
                    slotInsertTemplate();
                });
            menu->addSeparator();
        }

        menu->addAction(i18n("Add..."), q, [this]() {
                slotAdd();
            });
        if (!listSelectedIsEmpty) {
            const bool defaultTemplate = lstSelectedItems.first()->data(TemplateListWidget::DefaultTemplate).toBool();
            if (lstSelectedItems.count() == 1) {
                menu->addAction(defaultTemplate ? i18n("Show...") : i18n("Modify..."), q, [this]() {
                        slotModify();
                    });
                menu->addAction(i18n("Duplicate"), q, [this]() {
                        slotDuplicate();
                    });
            }
            if (lstSelectedItems.count() == 1 && !defaultTemplate) {
                menu->addSeparator();
                menu->addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove"), q, [this]() {
                        slotRemove();
                    });
            }
        }
        menu->addSeparator();
        if (q->count() > 0) {
            menu->addAction(i18n("Export..."), q, [this]() {
                    slotExportTemplates();
                });
        }
        menu->addAction(i18n("Import..."), q, [this]() {
                slotImportTemplates();
            });

        if (KAuthorized::authorize(QStringLiteral("ghns"))) {
            if (!knewstuffConfigName.isEmpty()) {
                menu->addSeparator();
                menu->addAction(QIcon::fromTheme(QStringLiteral("get-hot-new-stuff")), i18n("Download new Templates..."), q, [this]() {
                        slotDownloadTemplates();
                    });
            }
        }

        menu->exec(q->mapToGlobal(pos));
        delete menu;
    }

    void load()
    {
        q->clear();
        const QVector<PimCommon::defaultTemplate> templatesLst = q->defaultTemplates();
        for (const PimCommon::defaultTemplate &tmp : templatesLst) {
            createListWidgetItem(tmp.name, tmp.text, true);
        }
        KConfigGroup group = config.data()->group("template");
        if (group.hasKey(QStringLiteral("templateCount"))) {
            loadTemplates(config.data());
        }
        dirty = false;
    }

    void loadTemplates(KConfig *configFile)
    {
        KConfigGroup group = configFile->group("template");
        if (group.hasKey(QStringLiteral("templateCount"))) {
            const int numberTemplate = group.readEntry("templateCount", 0);
            for (int i = 0; i < numberTemplate; ++i) {
                KConfigGroup templateGroup = configFile->group(QStringLiteral("templateDefine_%1").arg(i));
                const QString name = templateGroup.readEntry("Name", QString());
                const QString text = templateGroup.readEntry("Text", QString());

                createListWidgetItem(name, text, false);
            }
        } else {
            KMessageBox::error(q, i18n("\'%1\' is not a template file", configFile->name()), i18n("Load Template"));
        }
    }

    void saveTemplates(KConfig *configFile)
    {
        // clear everything
        const QStringList lst = configFile->groupList();
        for (const QString &group : lst) {
            configFile->deleteGroup(group);
        }
        int numberOfTemplate = 0;
        for (int i = 0; i < q->count(); ++i) {
            QListWidgetItem *templateItem = q->item(i);
            if (templateItem->data(TemplateListWidget::DefaultTemplate).toBool() == false) {
                KConfigGroup group = configFile->group(QStringLiteral("templateDefine_%1").arg(numberOfTemplate));
                group.writeEntry("Name", templateItem->text());
                group.writeEntry("Text", templateItem->data(TemplateListWidget::Text));
                ++numberOfTemplate;
            }
        }
        KConfigGroup group = configFile->group("template");
        group.writeEntry("templateCount", numberOfTemplate);
        configFile->sync();
    }

    void slotDownloadTemplates()
    {
        QPointer<KNS3::DownloadDialog> downloadThemesDialog = new KNS3::DownloadDialog(knewstuffConfigName);
        downloadThemesDialog->exec();
        delete downloadThemesDialog;
    }

    void save()
    {
        if (!dirty) {
            return;
        }

        saveTemplates(config.data());
        dirty = false;
    }

    QString knewstuffConfigName;
    bool dirty = false;
    KSharedConfig::Ptr config;
    TemplateListWidget *const q;
};

TemplateListWidget::TemplateListWidget(const QString &configName, QWidget *parent)
    : QListWidget(parent)
    , d(new TemplateListWidgetPrivate(configName, this))
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropMode(QAbstractItemView::DragDrop);

    connect(this, &TemplateListWidget::customContextMenuRequested, this, [this](QPoint p) {
            d->slotContextMenu(p);
        });
    connect(this, &TemplateListWidget::doubleClicked, this, [this]() {
            d->slotModify();
        });
    connect(this, &TemplateListWidget::insertNewTemplate, this, [this](const QString &tmp) {
            d->slotInsertNewTemplate(tmp);
        });
}

TemplateListWidget::~TemplateListWidget()
{
    delete d;
}

void TemplateListWidget::loadTemplates()
{
    d->load();
}

QVector<defaultTemplate> TemplateListWidget::defaultTemplates()
{
    return QVector<PimCommon::defaultTemplate>();
}

QStringList TemplateListWidget::mimeTypes() const
{
    const QStringList lst{
        QStringLiteral("text/plain")
    };
    return lst;
}

QMimeData *TemplateListWidget::mimeData(const QList<QListWidgetItem *> items) const
{
    if (items.isEmpty()) {
        return nullptr;
    }
    auto *mimeData = new QMimeData();
    QListWidgetItem *item = items.first();
    mimeData->setText(item->data(TemplateListWidget::Text).toString());
    return mimeData;
}

bool TemplateListWidget::addNewTemplate(QString &templateName, QString &templateScript)
{
    QPointer<TemplateEditDialog> dlg = new TemplateEditDialog(this);
    bool result = false;
    if (dlg->exec()) {
        templateName = dlg->templateName();
        templateScript = dlg->script();
        result = true;
    }
    delete dlg;
    return result;
}

bool TemplateListWidget::modifyTemplate(QString &templateName, QString &templateScript, bool defaultTemplate)
{
    QPointer<TemplateEditDialog> dlg = new TemplateEditDialog(this, defaultTemplate);
    dlg->setTemplateName(templateName);
    dlg->setScript(templateScript);
    bool result = false;
    if (dlg->exec()) {
        if (!defaultTemplate) {
            templateName = dlg->templateName();
            templateScript = dlg->script();
        }
        result = true;
    }
    delete dlg;
    return result;
}

void TemplateListWidget::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        event->ignore();
        return;
    }
    if (event->mimeData()->hasText()) {
        event->setDropAction(Qt::CopyAction);
        Q_EMIT insertNewTemplate(event->mimeData()->text());
        event->accept();
    }
    QListWidget::dropEvent(event);
}

void TemplateListWidget::setKNewStuffConfigFile(const QString &configName)
{
    d->knewstuffConfigName = configName;
}

void TemplateListWidget::addDefaultTemplate(const QString &templateName, const QString &templateScript)
{
    d->createListWidgetItem(templateName, templateScript, true);
}
}
