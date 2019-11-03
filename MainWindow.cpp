#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Utility/Utility.h"
#include "Http/ILoginOperation.h"
#include "Widgets/PromptWidget.h"
#include "Widgets/AvatarWidget.h"
#include "Widgets/UserPageWidget.h"
#include "Widgets/BookViewWidget.h"
#include "LoginDialog.h"

#include <QDir>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QCloseEvent>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("书斋-v%1.%2.%3").arg(BS_MAJOR_VERSION).arg(BS_MINOR_VERSION).arg(BS_REVERSION));
    showMaximized();

    // 初始化左侧导航栏按钮组
    mNavButtonGroup = ui->navButtonGroup;
    mNavButtonGroup->setId(ui->btnBookShelf, 0);
    mNavButtonGroup->setId(ui->btnBookGarden, 1);
    mNavButtonGroup->setId(ui->btnSetting, 2);

    // 阴影特效
    setShadowEffect(ui->leSearchBox, QColor(200, 210, 220, 100), 30.0, 0.0, 4.0);
    setShadowEffect(ui->navMenuWidget, QColor(200, 210, 220, 100), 30.0, 4.0);
    setShadowEffect(ui->btnRefresh, QColor(85, 118, 189, 180), 20.0, 0.0, 4.0);
    setShadowEffect(ui->btnLoadMore, QColor(85, 118, 189, 180), 20.0, 0.0, 4.0);

    // 设置滚动风格
    ui->lwLibraryView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->lwLibraryView->verticalScrollBar()->setSingleStep(15);
    ui->lwLibraryView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->lwLibraryView->verticalScrollBar()->setSingleStep(15);
    ui->lwLibraryView->loadBooksFromLibrary(false);

    initUserInfo();
    connections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connections()
{
    connect(mNavButtonGroup,
            static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            ui->stackedWidget,
            &QStackedWidget::setCurrentIndex);

    connect(mNavButtonGroup,
            static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton *btn) {
                ui->lbHeaderName->setText(btn->text());
    });

    connect(ui->lbAvatar, &AvatarWidget::onClick, [=] {
        if(mUser) {
            UserPageWidget *userPage = new UserPageWidget(this);
            connect(userPage, &UserPageWidget::logout, this, &MainWindow::logout);
            userPage->setAvatar(ui->lbAvatar->avator());
            userPage->setName(mUser->name());
            userPage->exec();
            userPage->deleteLater();
        } else {
            LoginDialog *loginPage = new LoginDialog(this);
            loginPage->exec();

            if (!loginPage->isExit()) {
                // 重新获取用户数据
                initUserInfo();
            }

            // 销毁登录页
            loginPage->deleteLater();
            loginPage = nullptr;
        }
    });

    // 加载借书列表
    connect(ui->btnRefresh, &QPushButton::clicked, [=] {
        if (isLogedin()) {
            ui->lwLentBooksView->loadLentBooksFromUser(mUser->id());
        }
    });

    // 加载更多
    connect(ui->btnLoadMore, &QPushButton::clicked, [=] {
        ui->lwLibraryView->loadBooksFromLibrary(true, ui->leSearchBox->text());
    });

    // 搜索
    connect(ui->leSearchBox, &QLineEdit::returnPressed, [=] {
        if (!ui->btnBookGarden->isChecked()) {
            ui->btnBookGarden->click();
        }
        ui->lwLibraryView->loadBooksFromLibrary(false, ui->leSearchBox->text());
    });
}

bool MainWindow::isLogedin()
{
    if (mUser) {
        return true;
    } else {
        new PromptWidget("您还没有登录，请登录", this, PromptWidget::PromptType::Alert);
        return false;
    }
}

void MainWindow::initUserInfo()
{
    mUser = ILoginOperation::getUser();

    if (mUser) {
        ui->lbNickName->setText(mUser->name());

        QString avatorPath = LocalUserCacheDirectory + "Image/";
        if (QFile(avatorPath + "avatar.png").exists()) {
            ui->lbAvatar->setAvatar(QPixmap(avatorPath + "avatar.png"));
        } else {
            QDir dir(avatorPath);
            if (!dir.exists()) {
                dir.mkpath(avatorPath);
            }

            // TODO: 单独抽出来
            // 获取用户头像
            HttpRequest *request = new HttpRequest;
            request->sendRequest(mUser->avatarUrl());
            connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {
                if (success) {
                    QPixmap pixmap;
                    if (!pixmap.loadFromData(data)) {
                        new PromptWidget("头像数据加载出错", this, PromptWidget::PromptType::Alert);
                    }
                    if (!pixmap.save(avatorPath + "avatar.png")) {
                        new PromptWidget("保存文件失败", this, PromptWidget::PromptType::Alert);
                    }

                    ui->lbAvatar->setAvatar(pixmap);
                } else {
                    // TODO:提示错误并设置为默认头像
                    new PromptWidget("头像获取失败，请检查网络", this, PromptWidget::PromptType::Alert);
                    ui->lbAvatar->setDefaultAvatar();
                }
            });
        }

        // 获取借书列表
        ui->lwLentBooksView->loadLentBooksFromUser(mUser->id());

        // 提示登录成功
        new PromptWidget("登录成功", this, PromptWidget::PromptType::Prompt);
    } else {
        // 设置默认用户头像
        ui->lbNickName->setText("点击登录");
        ui->lbAvatar->setDefaultAvatar();
    }
}

void MainWindow::logout()
{
    HttpRequest *request = new HttpRequest;

    // 目前只实现提供id告诉服务器该用户登出了。
    QString postData = QString("type=logout&id=%1").arg(mUser->id());
    request->sendRequest(UserLogInOut, HttpRequest::HttpRequestType::POST, postData);
    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &jsonData) {
        // TODO: 下一个版本加入登录日志，记录登录登出日志，方便维护
        Q_UNUSED(success);
        Q_UNUSED(jsonData);
    });

    if (!mUser.isNull()) {
        mUser.clear();
        mUser = nullptr;
    }

    ui->lwLentBooksView->clearBooks();
    ui->lbNickName->setText("点击登录");
    ui->lbAvatar->setDefaultAvatar();
}

/*
void MainWindow::getCategories()
{
    HttpRequest *request = new HttpRequest;
    //    request->sendRequest(Sort);
    request->sendRequest("http://api.aixdzs.com/sort");
    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {

        ui->lwClassificationView->clear();

        qDeleteAll(CategoryWidget::Categories);
        CategoryWidget::Categories.clear();

        QString jsonData(data);
        if (success) {
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);
            if (jsonError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();

                // TODO:后台中不要male, 使用categories
                if (jsonObj.contains("male")) {
                    QJsonValue jsonValue = jsonObj.value("male");
                    if (jsonValue.isArray()) {
                        QJsonArray array = jsonValue.toArray();
                        int nSize = array.size();
                        for (int i = 0; i < nSize; ++i) {
                            QJsonObject obj = array.at(i).toObject();

                            QString catName = obj.value("name").toString();
                            int bookCount = obj.value("bookCount").toString().toInt();
                            int id = obj.value("_id").toString().toInt();

                            CategoryWidget *cat = new CategoryWidget(catName, bookCount, id, this);
                            CategoryWidget::Categories.append(cat);

                            QListWidgetItem *item = new QListWidgetItem(ui->lwClassificationView);
                            item->setSizeHint(QSize(180, 90));

                            ui->lwClassificationView->addItem(item);
                            ui->lwClassificationView->setItemWidget(item, cat);
                        }
                    }
                }
            }
        } else {
            PromptWidget *prompt = new PromptWidget("图书分类信息获取失败，请检查网络", this);
            prompt->show(PromptWidget::PromptType::Alert);
        }
    });
}*/
