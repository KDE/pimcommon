/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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

/*!
 * \class PimCommon::TemplateListWidget
 * \brief The TemplateListWidget class provides a list widget for templates
 * \inmodule PimCommon
 * \inheaderfile PimCommon/TemplateListWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TemplateListWidget : public QListWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a TemplateListWidget.
     * @param configName The configuration name for storing templates
     * @param parent The parent widget
     */
    explicit TemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    /*!
     * Destructs the TemplateListWidget.
     */
    ~TemplateListWidget() override;

    // Need to load template in specific class to allow to use correct defaultTemplates function
    /*!
     * Loads templates from disk.
     */
    void loadTemplates();

    /*!
     * Returns the list of default templates.
     * @return A list of default templates
     */
    [[nodiscard]] virtual QList<PimCommon::defaultTemplate> defaultTemplates();
    /*!
     * Adds a new template.
     * @param templateName The name of the new template (in/out parameter)
     * @param templateScript The script content of the template (in/out parameter)
     * @return true if the template was added successfully
     */
    [[nodiscard]] virtual bool addNewTemplate(QString &templateName, QString &templateScript);
    /*!
     * Modifies an existing template.
     * @param templateName The name of the template to modify (in/out parameter)
     * @param templateScript The script content to modify (in/out parameter)
     * @param defaultTemplate Whether this is a default template
     * @return true if the template was modified successfully
     */
    [[nodiscard]] virtual bool modifyTemplate(QString &templateName, QString &templateScript, bool defaultTemplate);

    /*!
     * Sets the KNewStuff configuration file.
     * @param configName The configuration file name
     */
    void setKNewStuffConfigFile(const QString &configName);

    /*!
     * Adds a default template.
     * @param templateName The name of the template
     * @param templateScript The script content
     */
    void addDefaultTemplate(const QString &templateName, const QString &templateScript);

protected:
    /*!
     * Returns the MIME types supported for drag and drop.
     * @return A list of supported MIME types
     */
    [[nodiscard]] QStringList mimeTypes() const override;
    /*!
     * Creates MIME data for dragged items.
     * @param items The list of items being dragged
     * @return QMimeData containing the dragged items
     */
    [[nodiscard]] QMimeData *mimeData(const QList<QListWidgetItem *> &items) const override;
    /*!
     * Handles drop events.
     * @param event The drop event
     */
    void dropEvent(QDropEvent *event) override;
    /*!
     * Enumeration for template data roles.
     */
    enum TemplateData {
        Text = Qt::UserRole + 1,
        DefaultTemplate = Qt::UserRole + 2,
    };

Q_SIGNALS:
    /*!
     * Emitted when a template is selected for insertion.
     * @param template The template content to insert
     */
    void insertTemplate(const QString &);
    /*!
     * Emitted when a new template is created.
     * @param template The new template content
     */
    void insertNewTemplate(const QString &);

private:
    friend class TemplateListWidgetPrivate;
    std::unique_ptr<TemplateListWidgetPrivate> const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::defaultTemplate, Q_RELOCATABLE_TYPE);
