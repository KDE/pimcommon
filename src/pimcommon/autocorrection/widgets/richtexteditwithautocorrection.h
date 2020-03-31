/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

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

#ifndef RICHTEXTEDITWITHAUTOCORRECTION_H
#define RICHTEXTEDITWITHAUTOCORRECTION_H

#include "pimcommon_export.h"
#include <KPIMTextEdit/RichTextEditor>

namespace PimCommon {
class AutoCorrection;
class RichTextEditWithAutoCorrectionPrivate;
/**
 * @brief The RichTextEditWithAutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT RichTextEditWithAutoCorrection : public KPIMTextEdit::RichTextEditor
{
    Q_OBJECT
public:
    explicit RichTextEditWithAutoCorrection(QWidget *parent = nullptr);
    ~RichTextEditWithAutoCorrection() override;

    Q_REQUIRED_RESULT PimCommon::AutoCorrection *autocorrection() const;

    void setAutocorrection(PimCommon::AutoCorrection *autocorrect);

    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    RichTextEditWithAutoCorrectionPrivate *const d;
};
}

#endif // RICHTEXTEDITWITHAUTOCORRECTION_H
