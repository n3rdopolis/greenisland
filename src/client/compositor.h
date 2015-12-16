/****************************************************************************
 * This file is part of Green Island.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef GREENISLANDCLIENT_COMPOSITOR_H
#define GREENISLANDCLIENT_COMPOSITOR_H

#include <QtCore/QObject>

#include <GreenIsland/client/greenislandclient_export.h>

namespace GreenIsland {

namespace Client {

class CompositorPrivate;
class Region;
class Registry;
class Surface;

class GREENISLANDCLIENT_EXPORT Compositor : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Compositor)
public:
    Surface *createSurface(QObject *parent = Q_NULLPTR);
    Region *createRegion(QObject *parent = Q_NULLPTR);
    Region *createRegion(const QRegion &region, QObject *parent = Q_NULLPTR);

    static QByteArray interfaceName();

private:
    Compositor(QObject *parent = Q_NULLPTR);

    friend class Registry;
};

} // namespace Client

} // namespace GreenIsland

#endif // GREENISLANDCLIENT_COMPOSITOR_H
