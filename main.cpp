#include "MainWindow.h"
#include <QApplication>

#include "LoginDialog.h"

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载样式表
    QFile styleFile(qApp->applicationDirPath()+"/Theme/Light.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styles = styleFile.readAll();
    a.setStyleSheet(styles);
    styleFile.close();

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
    MainWindow mainWindow;

    // 销毁登录页
    loginPage->deleteLater();
    loginPage = nullptr;

//    mainWindow.showMaximized();

    return a.exec();
}
