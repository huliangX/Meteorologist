/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "roundrectitem.h"

#include <QtGui/QtGui>

RoundRectItem::RoundRectItem(const QRectF &rect, const QBrush &brush, QWidget *embeddedWidget)
    : QGraphicsRectItem(rect),
      brush(brush),
      timeLine(75),
      lastVal(0),
      opa(1),
      proxyWidget(0)
{
    connect(&timeLine, SIGNAL(valueChanged(qreal)),
            this, SLOT(updateValue(qreal)));
    
    if (embeddedWidget) {
        proxyWidget = new QGraphicsProxyWidget(this);
        proxyWidget->setFocusPolicy(Qt::StrongFocus);
        proxyWidget->setWidget(embeddedWidget);
    //modified to locate the refresh location
        proxyWidget->setGeometry(boundingRect().adjusted(0, 0, 0, 0));
    }
}
RoundRectItem::~RoundRectItem()
{
    delete proxyWidget;
}
void RoundRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //modified to locate the refresh location
    if (proxyWidget && proxyWidget->pos() != QPoint())
        proxyWidget->setGeometry(boundingRect().adjusted(0, 0, 0, 0));
}

QRectF RoundRectItem::boundingRect() const
{
    //prevent the widget jump when transform
    qreal penW = 0.5;
    qreal shadowW = 2.0;
    return rect().adjusted(-penW, -penW, penW + shadowW, penW + shadowW);
}

//when err or data hasn't been ready
void RoundRectItem::setPixmap(const QPixmap &pixmap)
{
    pix = pixmap;
    if (scene() && isVisible())
        update();
}

qreal RoundRectItem::opacity() const
{
    RoundRectItem *parent = parentItem() ? (RoundRectItem *)parentItem() : 0;
    return opa + (parent ? parent->opacity() : 0);
}

void RoundRectItem::setOpacity(qreal opacity)
{
    opa = opacity;
    update();
}

void RoundRectItem::updateValue(qreal value)
{
    lastVal = value;
    if (!proxyWidget)
        setTransform(QTransform().scale(1 - value / 10.0, 1 - value / 10.0));
}

void RoundRectItem::updateWidget( QWidget *embeddedWidget )
{
    proxyWidget->setWidget(embeddedWidget);
    proxyWidget->setGeometry(boundingRect().adjusted(0, 0, 0, 0));
}
