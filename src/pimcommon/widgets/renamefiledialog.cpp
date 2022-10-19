/*
 * SPDX-FileCopyrightText: 2011-2022 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "renamefiledialog.h"
#include <KIO/StatJob>
#include <KJobWidgets>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSeparator>
#include <KStandardGuiItem>
#include <QLineEdit>
#include <QPushButton>

#include <QCheckBox>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

using namespace PimCommon;

class Q_DECL_HIDDEN PimCommon::RenameFileDialog::RenameFileDialogPrivate
{
public:
    RenameFileDialogPrivate(const QUrl &_url, RenameFileDialog *qq)
        : url(_url)
        , q(qq)
    {
    }

    Q_REQUIRED_RESULT QString suggestName(const QUrl &baseURL, const QString &oldName);

    const QUrl url;
    QCheckBox *applyAll = nullptr;
    QPushButton *renameBtn = nullptr;
    QPushButton *suggestNewNameBtn = nullptr;
    QLineEdit *nameEdit = nullptr;
    RenameFileDialog *const q;
};

QString PimCommon::RenameFileDialog::RenameFileDialogPrivate::suggestName(const QUrl &baseURL, const QString &oldName)
{
    QString dotSuffix;
    QString suggestedName;
    QString basename = oldName;
    const QChar spacer(QLatin1Char(' '));

    // ignore dots at the beginning, that way "..aFile.tar.gz" will become "..aFile 1.tar.gz" instead of " 1..aFile.tar.gz"
    int index = basename.indexOf(QLatin1Char('.'));
    int continuous = 0;
    while (continuous == index) {
        index = basename.indexOf(QLatin1Char('.'), index + 1);
        ++continuous;
    }

    if (index != -1) {
        dotSuffix = basename.mid(index);
        basename.truncate(index);
    }

    const int pos = basename.lastIndexOf(spacer);

    if (pos != -1) {
        const QString tmp = basename.mid(pos + 1);
        bool ok;
        const int number = tmp.toInt(&ok);

        if (!ok) { // ok there is no number
            suggestedName = basename + spacer + QLatin1Char('1') + dotSuffix;
        } else {
            // yes there's already a number behind the spacer so increment it by one
            basename.replace(pos + 1, tmp.length(), QString::number(number + 1));
            suggestedName = basename + dotSuffix;
        }
    } else { // no spacer yet
        suggestedName = basename + spacer + QLatin1Char('1') + dotSuffix;
    }

    // Check if suggested name already exists
    bool exists = false;
    // TODO: network transparency. However, using NetAccess from a modal dialog
    // could be a problem, no? (given that it uses a modal widget itself....)
    if (baseURL.isLocalFile()) {
        exists = QFileInfo::exists(baseURL.toLocalFile() + QLatin1Char('/') + suggestedName);
    }

    if (!exists) {
        return suggestedName;
    } else { // already exists -> recurse
        return suggestName(baseURL, suggestedName);
    }
}

RenameFileDialog::RenameFileDialog(const QUrl &url, bool multiFiles, QWidget *parent)
    : QDialog(parent)
    , d(new RenameFileDialogPrivate(url, this))
{
    setWindowTitle(i18nc("@title:window", "File Already Exists"));
    auto pLayout = new QVBoxLayout(this);

    auto label = new QLabel(xi18n("A file named <filename>%1</filename> already exists. Do you want to overwrite it?", url.fileName()), this);
    pLayout->addWidget(label);

    auto renameLayout = new QHBoxLayout();
    pLayout->addLayout(renameLayout);

    d->nameEdit = new QLineEdit(this);
    renameLayout->addWidget(d->nameEdit);
    d->nameEdit->setClearButtonEnabled(true);
    d->nameEdit->setText(url.fileName());
    d->suggestNewNameBtn = new QPushButton(i18n("Suggest New &Name"), this);
    renameLayout->addWidget(d->suggestNewNameBtn);
    connect(d->suggestNewNameBtn, &QPushButton::clicked, this, &RenameFileDialog::slotSuggestNewNamePressed);

    auto overWrite = new QPushButton(this);
    KStandardGuiItem::assign(overWrite, KStandardGuiItem::Overwrite);
    connect(overWrite, &QPushButton::clicked, this, &RenameFileDialog::slotOverwritePressed);

    auto ignore = new QPushButton(i18n("&Ignore"), this);
    connect(ignore, &QPushButton::clicked, this, &RenameFileDialog::slotIgnorePressed);

    d->renameBtn = new QPushButton(i18n("&Rename"), this);
    connect(d->renameBtn, &QPushButton::clicked, this, &RenameFileDialog::slotRenamePressed);

    auto separator = new KSeparator(this);
    pLayout->addWidget(separator);

    auto layout = new QHBoxLayout();
    pLayout->addLayout(layout);

    if (multiFiles) {
        d->applyAll = new QCheckBox(i18n("Appl&y to All"), this);
        connect(d->applyAll, &QCheckBox::clicked, this, &RenameFileDialog::slotApplyAllPressed);
        layout->addWidget(d->applyAll);
        slotApplyAllPressed();
    }
    layout->addWidget(d->renameBtn);
    layout->addWidget(overWrite);
    layout->addWidget(ignore);
}

RenameFileDialog::~RenameFileDialog() = default;

void RenameFileDialog::slotOverwritePressed()
{
    if (d->applyAll && d->applyAll->isChecked()) {
        done(RENAMEFILE_OVERWRITEALL);
    } else {
        done(RENAMEFILE_OVERWRITE);
    }
}

void RenameFileDialog::slotIgnorePressed()
{
    if (d->applyAll && d->applyAll->isChecked()) {
        done(RENAMEFILE_IGNOREALL);
    } else {
        done(RENAMEFILE_IGNORE);
    }
}

void RenameFileDialog::slotRenamePressed()
{
    if (d->nameEdit->text().isEmpty()) {
        return;
    }

    bool fileExists = false;
    if (newName().isLocalFile()) {
        fileExists = QFile::exists(newName().path());
    } else {
        auto job = KIO::statDetails(newName(), KIO::StatJob::DestinationSide, KIO::StatBasic);
        KJobWidgets::setWindow(job, this);
        fileExists = job->exec();
    }

    if (fileExists) {
        KMessageBox::error(this, i18n("This filename \"%1\" already exists.", newName().toDisplayString(QUrl::PreferLocalFile)), i18n("File already exists"));
        return;
    }
    done(RENAMEFILE_RENAME);
}

void RenameFileDialog::slotApplyAllPressed()
{
    const bool enabled(!d->applyAll->isChecked());
    d->nameEdit->setEnabled(enabled);
    d->suggestNewNameBtn->setEnabled(enabled);
    d->renameBtn->setEnabled(enabled);
}

void RenameFileDialog::slotSuggestNewNamePressed()
{
    if (d->nameEdit->text().isEmpty()) {
        return;
    }

    auto destDirectory = d->url.adjusted(QUrl::RemoveFilename);
    d->nameEdit->setText(d->suggestName(destDirectory, d->nameEdit->text()));
}

QUrl RenameFileDialog::newName() const
{
    const QString fileName = d->nameEdit->text();

    auto newDest = d->url.adjusted(QUrl::RemoveFilename | QUrl::StripTrailingSlash);
    newDest.setPath(newDest.path() + QLatin1Char('/') + KIO::encodeFileName(fileName));

    return newDest;
}
