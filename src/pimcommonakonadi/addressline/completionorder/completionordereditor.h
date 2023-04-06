/* -*- c++ -*-
 * completionordereditor.h
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "pimcommonakonadi_export.h"
#include <QDialog>

namespace KLDAPWidgets
{
class LdapClientSearch;
}

namespace PimCommon
{
class CompletionOrderEditorPrivate;
/**
 * @brief The CompletionOrderEditor class
 */
class PIMCOMMONAKONADI_EXPORT CompletionOrderEditor : public QDialog
{
    Q_OBJECT

public:
    explicit CompletionOrderEditor(KLDAPWidgets::LdapClientSearch *ldapSearch, QWidget *parent = nullptr);
    ~CompletionOrderEditor() override;

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotOk();
    PIMCOMMONAKONADI_NO_EXPORT void readConfig();
    PIMCOMMONAKONADI_NO_EXPORT void writeConfig();
    std::unique_ptr<CompletionOrderEditorPrivate> const d;
};
} // namespace
