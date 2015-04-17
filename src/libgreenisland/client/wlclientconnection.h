/****************************************************************************
 * This file is part of Green Island.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef WLCLIENTCONNECTION_H
#define WLCLIENTCONNECTION_H

#include <QtCore/QObject>

struct wl_display;

namespace GreenIsland {

class WlClientConnectionPrivate;

class WlClientConnection : public QObject
{
    Q_OBJECT
public:
    WlClientConnection(QObject *parent = 0);
    ~WlClientConnection();

    wl_display *display() const;
    void setDisplay(wl_display *display);

    int socketFd() const;
    void setSocketFd(int fd);

    QString socketName() const;
    void setSocketName(const QString &socketName);

    void initializeConnection();

    void flush();

Q_SIGNALS:
    void connected();
    void failed();
    void eventsDispatched();

private:
    Q_DECLARE_PRIVATE(WlClientConnection)
    WlClientConnectionPrivate *const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_initConnection())
};

}

#endif // WLCLIENTCONNECTION_H
