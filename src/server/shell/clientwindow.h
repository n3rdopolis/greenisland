/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
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

#ifndef GREENISLAND_CLIENTWINDOW_H
#define GREENISLAND_CLIENTWINDOW_H

#include <QtCore/QObject>

#include <GreenIsland/QtWaylandCompositor/QWaylandOutput>
#include <GreenIsland/QtWaylandCompositor/QWaylandSurface>
#include <GreenIsland/QtWaylandCompositor/QWaylandQuickItem>

#include <GreenIsland/Server/ClientWindowView>

namespace GreenIsland {

namespace Server {

class ClientWindowPrivate;

class GREENISLANDSERVER_EXPORT ClientWindow : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ClientWindow)
    Q_PROPERTY(QWaylandSurface *surface READ surface CONSTANT)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(GreenIsland::Server::ClientWindow *parentWindow READ parentWindow NOTIFY parentWindowChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString appId READ appId NOTIFY appIdChanged)
    Q_PROPERTY(qint64 processId READ processId CONSTANT)
    Q_PROPERTY(QString iconName READ iconName NOTIFY iconNameChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QRect windowGeometry READ windowGeometry NOTIFY windowGeometryChanged)
    Q_PROPERTY(QRect taskIconGeometry READ taskIconGeometry WRITE setTaskIconGeometry NOTIFY taskIconGeometryChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool minimized READ isMinimized WRITE setMinimized NOTIFY minimizedChanged)
    Q_PROPERTY(bool maximized READ isMaximized NOTIFY maximizedChanged)
    Q_PROPERTY(bool fullScreen READ isFullScreen NOTIFY fullScreenChanged)
    Q_PROPERTY(QWaylandOutput *designedOutput READ designedOutput NOTIFY designedOutputChanged)
    Q_PRIVATE_PROPERTY(ClientWindow::d_func(), QQmlListProperty<GreenIsland::Server::ClientWindowView> views READ windowViews NOTIFY viewsChanged DESIGNABLE false)
    Q_PRIVATE_PROPERTY(ClientWindow::d_func(), QQmlListProperty<QWaylandOutput> outputs READ outputs NOTIFY outputsChanged DESIGNABLE false)
public:
    enum Type {
        Unknown = 0,
        TopLevel,
        Popup,
        Transient
    };
    Q_ENUM(Type)

    ClientWindow(QWaylandSurface *surface, QObject *parent = Q_NULLPTR);
    ~ClientWindow();

    QWaylandSurface *surface() const;

    Type type() const;

    ClientWindow *parentWindow() const;

    QString title() const;
    QString appId() const;
    qint64 processId() const;
    QString iconName() const;

    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    QPointF position() const;
    void setPosition(const QPointF &pos);

    QRect windowGeometry() const;

    QRect taskIconGeometry() const;
    void setTaskIconGeometry(const QRect &rect);

    bool isActive() const;
    void setActive(bool active);

    bool isMinimized() const;
    void setMinimized(bool minimized);

    bool isMaximized() const;
    bool isFullScreen() const;

    QWaylandOutput *designedOutput() const;

public Q_SLOTS:
    void lower();
    void raise();
    void move(const QPoint &position);

Q_SIGNALS:
    void typeChanged();
    void parentWindowChanged();
    void titleChanged();
    void appIdChanged();
    void iconNameChanged();
    void xChanged();
    void yChanged();
    void windowGeometryChanged();
    void taskIconGeometryChanged();
    void activeChanged();
    void minimizedChanged();
    void maximizedChanged();
    void fullScreenChanged();
    void designedOutputChanged();
    void viewsChanged();
    void outputsChanged();
    void pingRequested();
    void pong();
    void windowMenuRequested(QWaylandInputDevice *inputDevice,
                             const QPoint &position);
};

} // namespace Server

} // namespace GreenIsland

#endif // GREENISLAND_CLIENTWINDOW_H
