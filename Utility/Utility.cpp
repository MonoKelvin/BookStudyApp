#include "Utility.h"

#include <QGraphicsDropShadowEffect>

void setShadowEffect(QWidget *widget, const QColor &color, qreal radius, qreal xoffset, qreal yoffset)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(widget);
    effect->setOffset(xoffset, yoffset);
    effect->setColor(color);
    effect->setBlurRadius(radius);
    widget->setGraphicsEffect(effect);
}
