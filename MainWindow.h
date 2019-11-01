#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class UserModel;
class HttpRequest;
class QButtonGroup;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(UserModel *user = nullptr, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void connections(void);

private slots:
    void setUserBaseInfo(void);
    void getCategories(void);

private:
    Ui::MainWindow *ui;

    QButtonGroup *mNavButtonGroup;

    // 从登录页面传递过来的用户信息
    UserModel *mUser;

//    HttpRequest *mLogoutRequest;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
