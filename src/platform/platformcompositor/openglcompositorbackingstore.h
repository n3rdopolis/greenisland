/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OPENGLCOMPOSITORBACKINGSTORE_H
#define OPENGLCOMPOSITORBACKINGSTORE_H

#include <QtGui/QImage>
#include <QtGui/QRegion>
#include <QtGui/qpa/qplatformbackingstore.h>

#include <GreenIsland/platform/greenislandplatform_export.h>

class QOpenGLContext;
class QPlatformTextureList;

namespace GreenIsland {

namespace Platform {

class GREENISLANDPLATFORM_EXPORT OpenGLCompositorBackingStore : public QPlatformBackingStore
{
public:
    OpenGLCompositorBackingStore(QWindow *window);
    ~OpenGLCompositorBackingStore();

    QPaintDevice *paintDevice() Q_DECL_OVERRIDE;

    void beginPaint(const QRegion &region) Q_DECL_OVERRIDE;

    void flush(QWindow *window, const QRegion &region, const QPoint &offset) Q_DECL_OVERRIDE;
    void resize(const QSize &size, const QRegion &staticContents) Q_DECL_OVERRIDE;

    QImage toImage() const Q_DECL_OVERRIDE;
    void composeAndFlush(QWindow *window, const QRegion &region, const QPoint &offset,
                         QPlatformTextureList *textures, QOpenGLContext *context,
                         bool translucentBackground) Q_DECL_OVERRIDE;

    const QPlatformTextureList *textures() const { return m_textures; }

    void notifyComposited();

private:
    void updateTexture();

    QWindow *m_window;
    QImage m_image;
    QRegion m_dirty;
    uint m_bsTexture;
    QOpenGLContext *m_bsTextureContext;
    QPlatformTextureList *m_textures;
    QPlatformTextureList *m_lockedWidgetTextures;
};

} // namespace Platform

} // namespace GreenIsland

#endif // OPENGLCOMPOSITORBACKINGSTORE_H
