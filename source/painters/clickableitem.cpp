/*
 * Copyright (C) 2020 Cameron White
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "clickableitem.h"
#include "styles.h"

#include <QCursor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

template <typename GraphicsItemT>
ClickableItemT<GraphicsItemT>::ClickableItemT(
    const QString &tooltip, const ScoreClickEvent &click_event,
    const ConstScoreLocation &location, ScoreItem item)
    : myClickEvent(click_event), myLocation(location), myItem(item)
{
    this->setAcceptHoverEvents(true);
    this->setToolTip(tooltip);

    // Enable selection. The default implementations of mousePressEvent() and
    // mouseReleaseEvent() handle selection already.
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

template <typename GraphicsItemT>
void
ClickableItemT<GraphicsItemT>::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    myClickEvent.signal(myItem, myLocation);
}

template <typename GraphicsItemT>
void
ClickableItemT<GraphicsItemT>::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    this->setCursor(Qt::PointingHandCursor);
}

template <typename GraphicsItemT>
void
ClickableItemT<GraphicsItemT>::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    this->unsetCursor();
}

template <typename GraphicsItemT>
void
ClickableItemT<GraphicsItemT>::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *)
{
    // Override how the selection is drawn (default is to draw a black border).
    if (option->state & QStyle::State_Selected)
    {
        painter->fillRect(this->boundingRect(),
                          Styles::SelectionColor);
    }
}

template class ClickableItemT<QGraphicsItem>;
template class ClickableItemT<QGraphicsItemGroup>;
