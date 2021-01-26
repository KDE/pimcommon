/* -*- c++ -*-
 * completionordereditor.h
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KDEPIM_COMPLETIONORDEREDITOR_H
#define KDEPIM_COMPLETIONORDEREDITOR_H

#include "pimcommonakonadi_export.h"
#include <QDialog>

namespace KLDAP
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
    CompletionOrderEditor(KLDAP::LdapClientSearch *ldapSearch, QWidget *parent = nullptr);
    ~CompletionOrderEditor();

private Q_SLOTS:
    void slotOk();

private:
    void readConfig();
    void writeConfig();
    CompletionOrderEditorPrivate *const d;
};
} // namespace

#endif /* COMPLETIONORDEREDITOR_H */
