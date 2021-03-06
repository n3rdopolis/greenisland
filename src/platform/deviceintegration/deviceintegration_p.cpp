/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL$
 *
 * This file may be used under the terms of the GNU Lesser General Public
 * License version 2.1 or later as published by the Free Software Foundation
 * and appearing in the file LICENSE.LGPLv21 included in the packaging of
 * this file.  Please review the following information to ensure the
 * GNU Lesser General Public License version 2.1 requirements will be
 * met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 * Alternatively, this file may be used under the terms of the GNU General
 * Public License version 2.0 or later as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPLv2 included in the
 * packaging of this file.  Please review the following information to ensure
 * the GNU General Public License version 2.0 requirements will be
 * met: http://www.gnu.org/licenses/gpl-2.0.html.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "logging.h"
#include "deviceintegration/deviceintegration_p.h"
#include "deviceintegration/egldeviceintegration.h"

namespace GreenIsland {

namespace Platform {

/*
 * HardwareDetector
 */

class HardwareDetector
{
public:
    static QString detectHardware()
    {
        // Detect Wayland
        if (!qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY"))
            return QStringLiteral("wayland");

        // Detect X11
        if (!qEnvironmentVariableIsEmpty("DISPLAY"))
            return QStringLiteral("x11");

        // Detect Broadcom
        bool found = deviceModel().startsWith(QLatin1String("Raspberry"));
        if (!found) {
            QStringList paths = QStringList()
                    << QStringLiteral("/usr/bin/vcgencmd")
                    << QStringLiteral("/opt/vc/bin/vcgencmd")
                    << QStringLiteral("/proc/vc-cma");
            found = pathsExist(paths);
        }
        if (found)
            return QStringLiteral("brcm");

        // TODO: Detect Mali
        // TODO: Detect Vivante

        // Detect KMS/DRM
        if (QDir(QLatin1String("/sys/class/drm")).exists())
            return QStringLiteral("kms");

        return QString();
    }

    static QString deviceModel()
    {
        QFile file(QStringLiteral("/proc/device-tree/model"));
        if (file.open(QIODevice::ReadOnly)) {
            QString data = QString::fromUtf8(file.readAll());
            file.close();
            return data;
        }

        return QString();
    }

    static bool pathsExist(const QStringList &paths)
    {
        Q_FOREACH (const QString &path, paths) {
            if (QFile::exists(path))
                return true;
        }

        return false;
    }
};

/*
 * DeviceIntegration
 */

DeviceIntegration::DeviceIntegration()
    : m_integration(Q_NULLPTR)
{
    const QString preferred = HardwareDetector::detectHardware();
    QObject *lastInstance = Q_NULLPTR;
    QString lastKey;

    const QStringList paths = QCoreApplication::libraryPaths();
    qCDebug(lcDeviceIntegration)
            << "EGL device integration plugin lookup paths:"
            << qPrintable(paths.join(' '));

    qCDebug(lcDeviceIntegration)
            << "Preferred EGL device integration based on the hardware configuration:"
            << preferred;

    Q_FOREACH (const QString &path, paths) {
        const QDir dir(path + QStringLiteral("/greenisland/egldeviceintegration/"),
                       QLatin1String("*.so"),
                       QDir::SortFlags(QDir::NoSort),
                       QDir::NoDotAndDotDot | QDir::Files);
        const QFileInfoList infoList = dir.entryInfoList();

        Q_FOREACH (const QFileInfo &info, infoList) {
            QPluginLoader loader(info.filePath());
            if (!loader.load())
                continue;

            QJsonObject metaData = loader.metaData()[QLatin1String("MetaData")].toObject();

            if (!metaData.contains(QLatin1String("Hardware"))) {
                qCDebug(lcDeviceIntegration,
                        "Plugin doesn't have hardware information: skipping \"%s\"",
                        qPrintable(info.filePath()));
                loader.unload();
                continue;
            }

            QObject *instance = loader.instance();
            if (!instance) {
                loader.unload();
                continue;
            }

            const QString key = metaData.value(QLatin1String("Hardware")).toString();

            if (key == preferred) {
                qCDebug(lcDeviceIntegration,
                        "Using \"%s\" EGL device integration", qPrintable(key));
                EGLDeviceIntegrationPlugin *plugin = qobject_cast<EGLDeviceIntegrationPlugin *>(instance);
                m_integration = plugin->create();
                return;
            } else {
                delete lastInstance;
                lastInstance = instance;
                lastKey = key;
                continue;
            }
        }
    }

    // Failed to find the preferred integration: either use the last
    // plugin we found or fall back to the default implementation
    if (lastInstance) {
        qCDebug(lcDeviceIntegration,
                "Using \"%s\" EGL device integration", qPrintable(lastKey));
        EGLDeviceIntegrationPlugin *plugin = qobject_cast<EGLDeviceIntegrationPlugin *>(lastInstance);
        m_integration = plugin->create();
    } else {
        qCWarning(lcDeviceIntegration) << "Use base EGL device integration";
        m_integration = new EGLDeviceIntegration;
    }
}

DeviceIntegration::~DeviceIntegration()
{
    delete m_integration;
}

} // namespace Platform

} // namespace GreenIsland
