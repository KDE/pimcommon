/*
  Copyright (c) 2013-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef TEMPLATELISTWIDGET_H
#define TEMPLATELISTWIDGET_H

#include "pimcommon_export.h"
#include <QListWidget>

namespace PimCommon {
class TemplateListWidgetPrivate;

struct defaultTemplate {
    QString name;
    QString text;
};

class PIMCOMMON_EXPORT TemplateListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    ~TemplateListWidget() override;

    //Need to load template in specific class to allow to use correct defaultTemplates function
    void loadTemplates();

    Q_REQUIRED_RESULT virtual QVector<PimCommon::defaultTemplate> defaultTemplates();
    Q_REQUIRED_RESULT virtual bool addNewTemplate(QString &templateName, QString &templateScript);
    Q_REQUIRED_RESULT virtual bool modifyTemplate(QString &templateName, QString &templateScript, bool defaultTemplate);

    void setKNewStuffConfigFile(const QString &configName);

    void addDefaultTemplate(const QString &templateName, const QString &templateScript);

protected:
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const override;

    void dropEvent(QDropEvent *event) override;
    enum TemplateData {
        Text = Qt::UserRole + 1,
        DefaultTemplate = Qt::UserRole + 2
    };

Q_SIGNALS:
    void insertTemplate(const QString &);
    void insertNewTemplate(const QString &);

private:
    friend class TemplateListWidgetPrivate;
    TemplateListWidgetPrivate *const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::defaultTemplate, Q_MOVABLE_TYPE);
#endif // TEMPLATELISTWIDGET_H
