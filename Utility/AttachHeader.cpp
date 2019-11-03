#include "AttachHeader.h"

#include "Utility/Utility.h"

#include <QPushButton>
#include <QLabel>
#include <QLayout>

AttachHeader::AttachHeader(QObject *parent)
    : QObject(parent)
{

}

void AttachHeader::attach(const QString &title, QWidget *parent, QWidget *background)
{
    parent->setWindowFlags(parent->windowFlags() | Qt::FramelessWindowHint);
    parent->setAttribute(Qt::WA_TranslucentBackground);

    // 布局
    parent->layout()->setMargin(SHADOW_PADDING);
    background->layout()->setContentsMargins(SHADOW_PADDING, HEADER_HEIGHT + 40, SHADOW_PADDING, SHADOW_PADDING);

    // 窗口标题
    QLabel * lbHeader = new QLabel(title, parent);
    lbHeader->setObjectName(QString::fromUtf8("lbHeader_h2"));
    lbHeader->setAlignment(Qt::AlignCenter);
    lbHeader->setGeometry(SHADOW_PADDING, SHADOW_PADDING, parent->width() - 2 * SHADOW_PADDING, HEADER_HEIGHT);

    // 窗口的关闭按钮
    QPushButton * btnClose = new QPushButton("×", parent);
    btnClose->setObjectName(QString::fromUtf8("btnClose"));
    btnClose->setGeometry(parent->width() - HEADER_HEIGHT - SHADOW_PADDING, SHADOW_PADDING, HEADER_HEIGHT, HEADER_HEIGHT);
    btnClose->raise();

    // 关闭事件
    connect(btnClose, &QPushButton::clicked, parent, &QWidget::close);

    // 设置美化特效
    setShadowEffect(parent, QColor(160, 165, 170, 100), qreal(SHADOW_PADDING));
    setShadowEffect(lbHeader, QColor(200, 210, 220, 80), 30.0, 0.0, 4.0);
}
