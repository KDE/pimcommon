/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QListWidget>

namespace PimCommon
{
class TemplateListWidgetPrivate;

struct defaultTemplate {
    QString name;
    QString text;
};

/**
 * @brief The TemplateListWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TemplateListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    ~TemplateListWidget() override;

    // Need to load template in specific class to allow to use correct defaultTemplates function
    void loadTemplates();

    Q_REQUIRED_RESULT virtual QVector<PimCommon::defaultTemplate> defaultTemplates();
    Q_REQUIRED_RESULT virtual bool addNewTemplate(QString &templateName, QString &templateScript);
    Q_REQUIRED_RESULT virtual bool modifyTemplate(QString &templateName, QString &templateScript, bool defaultTemplate);

    void setKNewStuffConfigFile(const QString &configName);

    void addDefaultTemplate(const QString &templateName, const QString &templateScript);

protected:
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QList<QListWidgetItem *> &items) const override;
    void dropEvent(QDropEvent *event) override;
    enum TemplateData {
        Text = Qt::UserRole + 1,
        DefaultTemplate = Qt::UserRole + 2,
    };

Q_SIGNALS:
    void insertTemplate(const QString &);
    void insertNewTemplate(const QString &);

private:
    friend class TemplateListWidgetPrivate;
    std::unique_ptr<TemplateListWidgetPrivate> const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::defaultTemplate, Q_MOVABLE_TYPE);
