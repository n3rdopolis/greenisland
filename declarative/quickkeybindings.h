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

#ifndef QUICKKEYBINDINGS_H
#define QUICKKEYBINDINGS_H

#include <QtQml/QQmlListProperty>

#include <GreenIsland/Server/KeyBindings>

using namespace GreenIsland::Server;

class QuickKeyBindings : public KeyBindings
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<KeyBinding> keyBindings READ keyBindingsList DESIGNABLE false)
public:
    QuickKeyBindings(QObject *parent = Q_NULLPTR);

    QQmlListProperty<KeyBinding> keyBindingsList();

    static int keyBindingsCount(QQmlListProperty<KeyBinding> *list);
    static KeyBinding *keyBindingsAt(QQmlListProperty<KeyBinding> *list, int index);
};

#endif // QUICKKEYBINDINGS_H
