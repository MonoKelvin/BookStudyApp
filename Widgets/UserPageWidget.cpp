#include "UserPageWidget.h"
#include "ui_UserPageWidget.h"

#include "Utility/Utility.h"

UserPageWidget::UserPageWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPageWidget)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 布局
    this->layout()->setMargin(SHADOW_PADDING);
    ui->frameBackground->setContentsMargins(SHADOW_PADDING, HEADER_HEIGHT, SHADOW_PADDING, SHADOW_PADDING);

    // 窗口标题
    QLabel *lbHeader = new QLabel("用户详情", this);
    lbHeader->setObjectName(QString::fromUtf8("lbHeader_h2"));
    lbHeader->setAlignment(Qt::AlignCenter);
    lbHeader->setGeometry(SHADOW_PADDING, SHADOW_PADDING, width() - 2 * SHADOW_PADDING, HEADER_HEIGHT);

    // 窗口的关闭按钮
    QPushButton * btnClose = new QPushButton("×", this);
    btnClose->setObjectName(QString::fromUtf8("btnClose"));
    btnClose->setGeometry(width() - HEADER_HEIGHT - SHADOW_PADDING, SHADOW_PADDING, HEADER_HEIGHT, HEADER_HEIGHT);
    btnClose->raise();

    // 关闭事件
    connect(btnClose, &QPushButton::clicked, this, &UserPageWidget::close);

    // 设置美化特效
    setShadowEffect(this, QColor(160, 165, 170, 140), qreal(SHADOW_PADDING));
    setShadowEffect(lbHeader, QColor(200, 210, 220, 80), 30.0, 0.0, 4.0);
    setShadowEffect(ui->btnLogout, QColor(85, 118, 189, 180), 20.0, 0.0, 4.0);
}

UserPageWidget::~UserPageWidget()
{
    delete ui;
}

void UserPageWidget::setAvator(const QPixmap& pixmap)
{
    ui->lbUserAvator->setAvatar(pixmap);
    ui->lbUserAvator->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void UserPageWidget::setName(const QString &name)
{
    ui->lbUserName->setText(name);
}


