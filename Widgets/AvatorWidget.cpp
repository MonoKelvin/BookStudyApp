#include "AvatorWidget.h"

#include <QPainter>

AvatorWidget::AvatorWidget(QWidget *parent)
    : QLabel(parent)
{
    mAvator = QPixmap("qrc:/Icons/AppIcons/default_avator.png");
}

void AvatorWidget::mousePressEvent(QMouseEvent *event)
{
    emit onClick();
    QWidget::mousePressEvent(event);
}

void AvatorWidget::paintEvent(QPaintEvent *event)
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
