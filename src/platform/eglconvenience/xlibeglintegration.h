/****************************************************************************
 * This file is part of Green Island.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini
 * Copyright (C) 2015 The Qt Company Ltd.
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL213$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1, or version 3.
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

#ifndef GREENISLAND_XLIBEGLINTEGRATION_H
#define GREENISLAND_XLIBEGLINTEGRATION_H

#include <GreenIsland/Platform/EGLConvenience>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace GreenIsland {

namespace Platform {

class GREENISLANDPLATFORM_EXPORT XlibEglIntegration
{
public:
    static VisualID getCompatibleVisualId(Display *display, EGLDisplay eglDisplay, EGLConfig config);
};

} // namespace Platform

} // namespace GreenIsland

#endif // GREENISLAND_XLIBEGLINTEGRATION_H