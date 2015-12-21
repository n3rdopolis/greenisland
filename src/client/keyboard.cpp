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

#include "keyboard.h"
#include "keyboard_p.h"
#include "seat.h"
#include "surface_p.h"

#include <unistd.h>

namespace GreenIsland {

namespace Client {

/*
 * KeyboardPrivate
 */

KeyboardPrivate::KeyboardPrivate()
    : QtWayland::wl_keyboard()
    , seat(Q_NULLPTR)
    , focusSurface(Q_NULLPTR)
    , repeatRate(0)
    , repeatDelay(0)
{
}

KeyboardPrivate::~KeyboardPrivate()
{
    if (seat->version() >= 3)
        release();
    else
        wl_keyboard_destroy(object());
}

Keyboard *KeyboardPrivate::fromWlKeyboard(struct ::wl_keyboard *keyboard)
{
    QtWayland::wl_keyboard *wlKeyboard =
            static_cast<QtWayland::wl_keyboard *>(wl_keyboard_get_user_data(keyboard));
    return static_cast<KeyboardPrivate *>(wlKeyboard)->q_func();
}

void KeyboardPrivate::keyboard_keymap(uint32_t format, int32_t fd, uint32_t size)
{
    Q_Q(Keyboard);

    if (format != QtWayland::wl_keyboard::keymap_format_xkb_v1) {
        ::close(fd);
        return;
    }

    Q_EMIT q->keymapChanged(fd, size);
}

void KeyboardPrivate::keyboard_enter(uint32_t serial, struct ::wl_surface *surface, wl_array *keys)
{
    Q_UNUSED(keys);

    Q_Q(Keyboard);

    focusSurface = SurfacePrivate::fromWlSurface(surface);
    Q_EMIT q->enter(serial);
}

void KeyboardPrivate::keyboard_leave(uint32_t serial, struct ::wl_surface *surface)
{
    Q_UNUSED(surface);

    Q_Q(Keyboard);

    focusSurface = Q_NULLPTR;
    Q_EMIT q->leave(serial);
}

void KeyboardPrivate::keyboard_key(uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
    Q_UNUSED(serial);

    Q_Q(Keyboard);

    if (state == QtWayland::wl_keyboard::key_state_pressed)
        Q_EMIT q->keyPressed(time, key);
    else
        Q_EMIT q->keyReleased(time, key);
}

void KeyboardPrivate::keyboard_modifiers(uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{
    Q_UNUSED(serial);

    Q_Q(Keyboard);

    Q_EMIT q->modifiersChanged(mods_depressed, mods_latched, mods_locked, group);
}

void KeyboardPrivate::keyboard_repeat_info(int32_t rate, int32_t delay)
{
    Q_Q(Keyboard);

    if (qint32(repeatRate) != rate) {
        repeatRate = qMax(rate, 0);
        Q_EMIT q->repeatRateChanged();
    }

    if (qint32(repeatDelay) != delay) {
        repeatDelay = qMax(delay, 0);
        Q_EMIT q->repeatDelayChanged();
    }
}

/*
 * Keyboard
 */

Keyboard::Keyboard(Seat *seat)
    : QObject(*new KeyboardPrivate(), seat)
{
}

Surface *Keyboard::focusSurface() const
{
    Q_D(const Keyboard);
    return d->focusSurface;
}

quint32 Keyboard::repeatRate() const
{
    Q_D(const Keyboard);
    return d->repeatRate;
}

quint32 Keyboard::repeatDelay() const
{
    Q_D(const Keyboard);
    return d->repeatDelay;
}

QByteArray Keyboard::interfaceName()
{
    return QByteArrayLiteral("wl_keyboard");
}

} // namespace Client

} // namespace GreenIsland