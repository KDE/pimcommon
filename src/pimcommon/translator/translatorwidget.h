/*

  Copyright (c) 2012-2020 Laurent Montel <montel@kde.org>

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

#ifndef TRANSLATORWIDGET_H
#define TRANSLATORWIDGET_H

#include "pimcommon_export.h"
#include <KPIMTextEdit/PlainTextEditor>
#include <kio/job.h>
#include <KPIMTextEdit/PlainTextEditorWidget>
namespace PimCommon {
class TranslatorResultTextEdit : public KPIMTextEdit::PlainTextEditor
{
    Q_OBJECT
public:
    explicit TranslatorResultTextEdit(QWidget *parent = nullptr);

    void setResultFailed(bool failed);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool mResultFailed;
};

/**
 * @brief The TranslatorTextEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TranslatorTextEdit : public KPIMTextEdit::PlainTextEditor
{
    Q_OBJECT
public:
    explicit TranslatorTextEdit(QWidget *parent = nullptr);

Q_SIGNALS:
    void translateText();

protected:
    void dropEvent(QDropEvent *) override;
};

/**
 * @brief The TranslatorWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TranslatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorWidget(QWidget *parent = nullptr);
    explicit TranslatorWidget(const QString &text, QWidget *parent = nullptr);
    ~TranslatorWidget() override;

    void setTextToTranslate(const QString &);
    void writeConfig();
    void readConfig();
    void setStandalone(bool b);

public Q_SLOTS:
    void slotTranslate();
    void slotCloseWidget();

private Q_SLOTS:
    void slotFromLanguageChanged(int, bool initialize = false);
    void slotTextChanged();
    void slotInvertLanguage();
    void slotClear();
    void slotTranslateDone();
    void slotTranslateFailed(bool result, const QString &message);
    void slotDebug();
    void slotConfigChanged();

protected:
    bool event(QEvent *e) override;

Q_SIGNALS:
    void toolsWasClosed();

private:
    void init();
    void initLanguage();
    class TranslatorWidgetPrivate;
    TranslatorWidgetPrivate *const d;
};
}

#endif /* TRANSLATORWIDGET_H */
