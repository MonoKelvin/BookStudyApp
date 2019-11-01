﻿#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "Utility/Utility.h"
#include "Utility/BookStudyAPI.h"
#include "Http/LoginWithQQMail.h"
#include "Widgets/PromptWidget.h"

#include <QLabel>
#include <QScreen>
#include <QDebug>
#include <QDir>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 左上角的诗句
    QLabel *verse = new QLabel(this);
    verse->setObjectName("lbVerse");
    verse->setText("直\n当\n花\n院\n里\n，\n书\n斋\n望\n晓\n开\n。");
    verse->setAlignment(Qt::AlignTop);
    verse->setGeometry(15, 15, 50, height() - 30);

    //获取主屏幕分辨率
    QSize screenSize = QApplication::primaryScreen()->size();
    QSize lt = screenSize - this->size();
    this->setFixedSize(1000, 618);
    this->setGeometry(lt.width() / 2, lt.height() / 2, width(), height());
    this->setWindowTitle(QString("书斋-v%1.%2.%3").arg(BS_MAJOR_VERSION).arg(BS_MINOR_VERSION).arg(BS_REVERSION));

    // 初始化登录、注册页面控件显隐和相关参数
    mIsSignUp = false;
    mIsExit = false;
    ui->leRecheckPwd->setHidden(true);
    ui->leNickName->setHidden(true);

    // 登录方式默认初始化为账号密码登录
    mLoginMethod = new LoginWithQQMail;

    // TODO: 发布时删除
    ui->leInputAccount->setText("15007083506@qq.com");
    ui->leInputPassword->setText("pwd123");

    connections();
}

LoginDialog::~LoginDialog()
{
    mLoginMethod->deleteLater();
    delete ui;
}

bool LoginDialog::loggedIn()
{
    bool loginStatus = false;

    QDir userDir(BookStudyAPI::LocalUserLoginDirectory);
    if (!userDir.exists()) {
        userDir.mkdir(BookStudyAPI::LocalUserLoginDirectory);
    } else {
        // 找到用户信息文件夹下的UserData.bls的文件
        // UserData.bls文件是加密过的MD5二进制文件，后缀表示 binary login info
        QFile md5File(BookStudyAPI::LocalUserLoginDirectory + "UserData.bli");

        if (md5File.exists()) {
            loginStatus = true;
            // 发送请求
        } else {

        }
        md5File.close();
    }

    return loginStatus;
}

void LoginDialog::connections()
{
    // 当点击 登录/注册 按钮，进行 验证登录/提交注册
    connect(ui->btnLogin, &QPushButton::clicked, [=] {
        if (mIsSignUp) {
            // TODO: 实现注册功能
        } else {
            QMap<QString, QString> mapping;
            mapping["account"] = ui->leInputAccount->text();
            mapping["password"] = ui->leInputPassword->text();
            mLoginMethod->verify(mapping);
        }
    });

    // 当登录成功时，会返回一个用户信息模型
    connect(mLoginMethod, &ILoginOperation::login, [=](UserModel *user) {
        mUser = user;
        if (mUser != nullptr) {
            this->accept();
        } else {
            PromptWidget *prompt = new PromptWidget("用户数据获取失败，请重新登录", this);
            prompt->show(PromptWidget::PromptType::Alert);
        }
    });

    // 登录失败
    connect(mLoginMethod, &ILoginOperation::failed, [=] {
        PromptWidget *prompt = new PromptWidget("登录失败，请检查账号或密码是否正确", this);
        prompt->show(PromptWidget::PromptType::Alert);
    });

    // 点击注册按钮实现的登录、注册切换功能
    connect(ui->btnSignUp, &QPushButton::clicked, [=] {
        ui->leRecheckPwd->setHidden(mIsSignUp);
        ui->leNickName->setHidden(mIsSignUp);
        mIsSignUp = !mIsSignUp;

        if (mIsSignUp) {
            ui->lbNoAccount->setText("已有账号？");
            ui->btnSignUp->setText("返回登录");
            ui->lbLogin->setText("注册");
            ui->btnLogin->setText("注册");
            ui->leInputAccount->clear();
            ui->leInputPassword->clear();
        } else {
            ui->lbNoAccount->setText("没有帐号？");
            ui->btnSignUp->setText("点击注册");
            ui->lbLogin->setText("登录");
            ui->btnLogin->setText("登录");
        }
        ui->leRecheckPwd->clear();
        ui->leNickName->clear();
    });

    // 当登录页面退出时
    connect(this, &QDialog::rejected, [=] {
        mIsExit = true;
    });
}
