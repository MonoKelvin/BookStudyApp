#include "MainWindow.h"
#include <QApplication>

#include "LoginDialog.h"

// 用于测试的管理员id\md5
// id = 1; md5 = f2d2b9ae2d741a04634adfe18e2ea2c0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 登录页面
    LoginDialog *loginPage = new LoginDialog;
    loginPage->exec();

    // 如果退出登录就销毁
    if (loginPage->isExit()) {
        loginPage->deleteLater();
        loginPage = nullptr;
        return 0;
    }

    // 主页面
    MainWindow mainWindow(loginPage->getUser());

    // 销毁登录页
    loginPage->deleteLater();
    loginPage = nullptr;

    mainWindow.showMaximized();

    return a.exec();
}
