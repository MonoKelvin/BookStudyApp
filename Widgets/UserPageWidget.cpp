#include "UserPageWidget.h"
#include "ui_UserPageWidget.h"

#include "Utility/Utility.h"
#include "Utility/AttachHeader.h"

UserPageWidget::UserPageWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPageWidget)
{
    ui->setupUi(this);

    AttachHeader::attach("用户详情", this, ui->frameBackground);

    connect(ui->btnLogout, &QPushButton::clicked, [=] {
        emit logout();
        this->accept();
    });

    setShadowEffect(ui->btnLogout, QColor(85, 118, 189, 180), 20.0, 0.0, 4.0);
}

UserPageWidget::~UserPageWidget()
{
    delete ui;
}

void UserPageWidget::setAvatar(const QPixmap& pixmap)
{
    ui->lbUserAvatar->setAvatar(pixmap);
    ui->lbUserAvatar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void UserPageWidget::setName(const QString &name)
{
    ui->lbUserName->setText(name);
}


