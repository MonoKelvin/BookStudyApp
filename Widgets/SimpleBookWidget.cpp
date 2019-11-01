#include "SimpleBookWidget.h"

#include <QVBoxLayout>

SimpleBookWidget::SimpleBookWidget(QWidget *parent)
    : QWidget(parent)
{
//    setCursor(Qt::PointingHandCursor);
}

SimpleBookWidget::SimpleBookWidget(unsigned int id, QWidget *parent)
    : QWidget(parent)
    , mID(id)
{
}
