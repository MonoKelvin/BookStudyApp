﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class UserModel;
class QButtonGroup;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void connections(void);
    bool isLogedin(void);
    void initUserInfo(void);

    inline void destroyUser(void) {
        if (!mUser.isNull()) {
            mUser.clear();
            mUser = nullptr;
        }
    }

    void closeEvent(QCloseEvent *event) override;

private slots:
    void logout();

private:
    Ui::MainWindow *ui;

    QButtonGroup *mNavButtonGroup;

    // 从登录页面传递过来的用户信息
    QSharedPointer<UserModel> mUser;
};

#endif // MAINWINDOW_H
