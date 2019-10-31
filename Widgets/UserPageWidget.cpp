#include "UserPageWidget.h"
#include "ui_UserPageWidget.h"

#include <QPainter>

UserPageWidget::UserPageWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPageWidget)
{
    ui->setupUi(this);
}

UserPageWidget::~UserPageWidget()
{
    delete ui;
}

void UserPageWidget::setAvator(const QPixmap& pixmap)
{
    ui->lbUserAvator->setPixmap(pixmap);
}

void UserPageWidget::setNickName(const QString &nickName)
{
    ui->lbUserNickName->setText(nickName);
}


