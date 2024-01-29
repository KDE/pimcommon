/*
  SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createresource.h"

#include "pimcommonakonadi_debug.h"
#include <KLocalizedString>

#include <Akonadi/AgentInstanceCreateJob>
#include <Akonadi/AgentManager>
#include <Akonadi/AgentType>

#include <QDBusInterface>
#include <QDBusReply>
#include <QMetaMethod>

using namespace Akonadi;

using namespace PimCommon;

CreateResource::CreateResource(QObject *parent)
    : QObject(parent)
{
}

CreateResource::~CreateResource() = default;

// code from accountwizard
static QMetaType::Type argumentType(const QMetaObject *mo, const QString &method)
{
    QMetaMethod m;
    const int numberOfMethod(mo->methodCount());
    for (int i = 0; i < numberOfMethod; ++i) {
        const QString signature = QString::fromLatin1(mo->method(i).methodSignature());
        if (signature.contains(method + QLatin1Char('('))) {
            m = mo->method(i);
            break;
        }
    }

    if (m.methodSignature().isEmpty()) {
        qCWarning(PIMCOMMONAKONADI_LOG) << "Did not find D-Bus method: " << method << " available methods are:";
        for (int i = 0; i < numberOfMethod; ++i) {
            qCWarning(PIMCOMMONAKONADI_LOG) << mo->method(i).methodSignature();
        }
        return QMetaType::UnknownType;
    }

    const QList<QByteArray> argTypes = m.parameterTypes();
    if (argTypes.count() != 1) {
        return QMetaType::UnknownType;
    }

    return static_cast<QMetaType::Type>(QMetaType::fromName(argTypes.first().constData()).id());
}

QString CreateResource::createResource(const QString &resources, const QString &name, const QMap<QString, QVariant> &settings, bool synchronizeTree)
{
    const AgentType type = AgentManager::self()->type(resources);
    if (!type.isValid()) {
        Q_EMIT createResourceError(i18n("Resource type '%1' is not available.", resources));
        return {};
    }

    // check if unique instance already exists
    qCDebug(PIMCOMMONAKONADI_LOG) << type.capabilities();
    if (type.capabilities().contains(QLatin1StringView("Unique"))) {
        const AgentInstance::List lstInstances = AgentManager::self()->instances();
        for (const AgentInstance &instance : lstInstances) {
            qCDebug(PIMCOMMONAKONADI_LOG) << instance.type().identifier() << (instance.type() == type);
            if (instance.type() == type) {
                Q_EMIT createResourceInfo(i18n("Resource '%1' is already set up.", type.name()));
                return {};
            }
        }
    }

    Q_EMIT createResourceInfo(i18n("Creating resource instance for '%1'...", type.name()));
    auto job = new AgentInstanceCreateJob(type, this);
    if (job->exec()) {
        Akonadi::AgentInstance instance = job->instance();

        if (!settings.isEmpty()) {
            Q_EMIT createResourceInfo(i18n("Configuring resource instance..."));
            QDBusInterface iface(QLatin1StringView("org.freedesktop.Akonadi.Resource.") + instance.identifier(), QStringLiteral("/Settings"));
            if (!iface.isValid()) {
                Q_EMIT createResourceError(i18n("Unable to configure resource instance."));
                return {};
            }

            // configure resource
            if (!name.isEmpty()) {
                instance.setName(name);
            }
            const QMap<QString, QVariant>::const_iterator end(settings.constEnd());
            for (QMap<QString, QVariant>::const_iterator it = settings.constBegin(); it != end; ++it) {
                qCDebug(PIMCOMMONAKONADI_LOG) << "Setting up " << it.key() << " for agent " << instance.identifier();
                const QString methodName = QStringLiteral("set%1").arg(it.key());
                QVariant arg = it.value();
                const QMetaType::Type targetType = argumentType(iface.metaObject(), methodName);
                if (arg.metaType().id() != targetType) {
                    Q_EMIT createResourceError(
                        i18n("Could not convert value of setting '%1' to required type %2.", it.key(), QString::fromLatin1(QMetaType(targetType).name())));
                    return {};
                }
                QDBusReply<void> reply = iface.call(methodName, arg);
                if (!reply.isValid()) {
                    Q_EMIT createResourceError(i18n("Could not set setting '%1': %2", it.key(), reply.error().message()));
                    return {};
                }
            }
            QDBusReply<void> reply = iface.call(QStringLiteral("save"));
            if (!reply.isValid()) {
                Q_EMIT createResourceError(i18n("Could not save settings: %1", reply.error().message()));
                return {};
            }
            instance.reconfigure();
            if (synchronizeTree) {
                instance.synchronizeCollectionTree();
            }
        }

        Q_EMIT createResourceInfo(i18n("Resource setup completed."));
        return instance.identifier();
    } else {
        if (job->error()) {
            Q_EMIT createResourceError(i18n("Failed to create resource instance: %1", job->errorText()));
        }
    }
    return {};
}

#include "moc_createresource.cpp"
