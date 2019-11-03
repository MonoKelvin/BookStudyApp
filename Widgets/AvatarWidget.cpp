#include "AvatarWidget.h"

#include <QPainter>

AvatarWidget::AvatarWidget(QWidget *parent)
    : QLabel(parent)
{
    mAvator = QPixmap("qrc:/Icon/AppIcons/default_avatar.png");
}

void AvatarWidget::mousePressEvent(QMouseEvent *event)
{
    emit onClick();
    QWidget::mousePressEvent(event);
}

void AvatarWidget::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addEllipse(rect());
    painter.setClipPath(path);

    painter.drawPixmap(rect(), mAvator);

    QLabel::paintEvent(event);
}
