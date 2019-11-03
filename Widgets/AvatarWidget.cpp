#include "AvatarWidget.h"

#include <QDebug>
#include <QPainter>

AvatarWidget::AvatarWidget(QWidget *parent)
    : QLabel(parent)
{
    setDefaultAvatar();
}

void AvatarWidget::mousePressEvent(QMouseEvent *event)
{
    emit onClick();
    QWidget::mousePressEvent(event);
}

void AvatarWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addEllipse(rect());
    painter.setClipPath(path);
    painter.drawPixmap(rect(), mAvator);
}
