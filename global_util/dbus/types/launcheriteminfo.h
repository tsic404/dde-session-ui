/*
 * Copyright (C) 2017 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     LiLinling <lilinling_cm@deepin.com>
 *
 * Maintainer: LiLinling <lilinling_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <QtCore/QString>
#include <QtDBus/QtDBus>
#include <QtCore/QList>
#include <QDBusMetaType>
#include <QDebug>

struct LauncherItemInfo {
    QString path;
    QString name;
    QString id;
    QString icon;
    qint64 categoryId;
    qint64 timeInstalled;
    QStringList keywords;
    bool operator!=(const LauncherItemInfo &versionInfo);

    friend QDebug operator<<(QDebug argument, const LauncherItemInfo &info)
    {
        argument << info.path << info.name << info.id;
        argument << info.icon << info.categoryId << info.timeInstalled << info.keywords;

        return argument;
    }
};

Q_DECLARE_METATYPE(LauncherItemInfo)

QDBusArgument &operator<<(QDBusArgument &argument, const LauncherItemInfo &versionInfo);
const QDBusArgument &operator>>(const QDBusArgument &argument, LauncherItemInfo &versionInfo);
void registerLauncherItemInfoMetaType();
