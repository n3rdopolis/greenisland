/****************************************************************************
 * This file is part of Green Island.
 *
 * Copyright (C) 2014-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef GREENISLAND_WINDOWVIEW_H
#define GREENISLAND_WINDOWVIEW_H

#include <GreenIsland/Compositor/QWaylandSurfaceItem>

#include <GreenIsland/server/greenislandserver_export.h>

namespace GreenIsland {

class GREENISLANDSERVER_EXPORT WindowView : public QWaylandSurfaceItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF localPosition READ localPosition NOTIFY localPositionChanged)
    Q_PROPERTY(qreal localX READ localX NOTIFY localPositionChanged)
    Q_PROPERTY(qreal localY READ localY NOTIFY localPositionChanged)
public:
    WindowView(QWaylandQuickSurface *surface, QQuickItem *parent = 0);

    QPointF localPosition() const;
    void setLocalPosition(const QPointF &pt);

    qreal localX() const;
    qreal localY() const;

Q_SIGNALS:
    void localPositionChanged();
    void mousePressed();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPointF m_pos;

    void takeFocus(QWaylandInputDevice *device = 0) Q_DECL_OVERRIDE;

    void startMove();
    void stopMove();
};

}

#endif // GREENISLAND_WINDOWVIEW_H
