/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "storageserviceinterface.h"
using namespace PimCommon;

StorageServiceInterface::StorageServiceInterface(QObject *parent)
    : QObject(parent)
{
}

StorageServiceInterface::~StorageServiceInterface()
{
}

void StorageServiceInterface::downloadFile(const QString &name, const QString &fileId, const QString &destination)
{
    Q_UNUSED(name);
    Q_UNUSED(fileId);
    Q_UNUSED(destination);
}

void StorageServiceInterface::uploadFile(const QString &filename, const QString &uploadAsName, const QString &destination)
{
    Q_UNUSED(filename);
    Q_UNUSED(uploadAsName);
    Q_UNUSED(destination);
}

void StorageServiceInterface::accountInfo()
{
}

void StorageServiceInterface::createFolder(const QString &foldername, const QString &destination)
{
    Q_UNUSED(foldername);
    Q_UNUSED(destination);
}

void StorageServiceInterface::listFolder(const QString &folder)
{
    Q_UNUSED(folder);
}

void StorageServiceInterface::authentication()
{
}

void StorageServiceInterface::shareLink(const QString &root, const QString &path)
{
    Q_UNUSED(root);
    Q_UNUSED(path);
}

void StorageServiceInterface::createServiceFolder()
{
}

void StorageServiceInterface::deleteFile(const QString &filename)
{
    Q_UNUSED(filename);
}

void StorageServiceInterface::deleteFolder(const QString &foldername)
{
    Q_UNUSED(foldername);
}

void StorageServiceInterface::renameFolder(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::renameFile(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::moveFile(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::moveFolder(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::copyFile(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::copyFolder(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
}

void StorageServiceInterface::removeConfig()
{
    //TODO
}
