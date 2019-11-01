#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Utility/Utility.h"
#include "Http/ILoginOperation.h"
#include "Widgets/CategoryWidget.h"
#include "Widgets/PromptWidget.h"
#include "Widgets/AvatorWidget.h"
#include "Widgets/UserPageWidget.h"
#include "Widgets/BookViewWidget.h"

#include <QCloseEvent>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(UserModel *user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mUser = user;

    mNavButtonGroup = ui->navButtonGroup;
    mNavButtonGroup->setId(ui->btnBookShelf, 0);
    mNavButtonGroup->setId(ui->btnBookGarden, 1);
    mNavButtonGroup->setId(ui->btnSetting, 2);

    setShadowEffect(ui->leSearchBox, QColor(200, 210, 220, 100), 30.0, 0.0, 4.0);
    setShadowEffect(ui->navMenuWidget, QColor(200, 210, 220, 100), 30.0, 4.0);
    // setShadowEffect(ui->toolBarWidget, QColor(200, 210, 210, 200), 30.0, -4.0);
    setShadowEffect(ui->btnLoadMore, QColor(85, 118, 189, 180), 20.0, 0.0, 4.0);

    setUserBaseInfo();
    ui->lwLentBooksView->loadLentBooksFromUser(mUser->id());
    ui->lwLibraryView->loadBooksFromLibrary();
//    getCategories();

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

    connect(ui->lbAvator, &AvatorWidget::onClick, [=] {
        // TODO: 用户详情
        UserPageWidget *userPage = new UserPageWidget(this);
        userPage->setAvator(ui->lbAvator->avator());
        userPage->setNickName(mUser->nickName());
        userPage->exec();
        userPage->deleteLater();
    });

    connect(ui->btnLoadMore, &QPushButton::clicked, ui->lwLibraryView, &BookViewWidget::loadBooksFromLibrary);

//    connect(mLogoutRequest, &HttpRequest::request, [=](bool success, const QByteArray &data) {
//        // todo: 下一个版本加入【退出时提醒用户快到还书时间】
//        Q_UNUSED(success);
//        Q_UNUSED(data);
//        qDebug() << "data";
//    });
}

void MainWindow::setUserBaseInfo()
{
    if (mUser) {
        ui->lbNickName->setText(mUser->nickName());

        QString avatorPath = LocalUserCacheDirectory + "Image/";

        if (QFile(avatorPath + "avatar.png").exists()) {
            ui->lbAvator->setAvatar(QPixmap(avatorPath + "avatar.png"));
        } else {
            QDir dir(avatorPath);
            if (!dir.exists()) {
                dir.mkpath(avatorPath);
            }

            HttpRequest *request = new HttpRequest;
            request->sendRequest(mUser->avatarUrl());

            connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {
                if (success) {
                    QPixmap pixmap;
                    if (!pixmap.loadFromData(data)) {
                        PromptWidget *prompt = new PromptWidget("头像数据加载出错", this);
                        prompt->show(PromptWidget::PromptType::Alert);
                    }
                    if (!pixmap.save(avatorPath + "avatar.png")) {
                        PromptWidget *prompt = new PromptWidget("保存文件失败", this);
                        prompt->show(PromptWidget::PromptType::Alert);
                    }

                    ui->lbAvator->setAvatar(pixmap);
                } else {
                    // TODO:提示错误并设置为默认头像
                    PromptWidget *prompt = new PromptWidget("头像获取失败，请检查网络", this);
                    prompt->show(PromptWidget::PromptType::Alert);
                    ui->lbAvator->setAvatar(QPixmap("qrc:/Icons/AppIcons/default_avatar.png"));
                }
            });
        }
    } else {
        PromptWidget *prompt = new PromptWidget("用户数据加载出错，请重新登录", this);
        prompt->show(PromptWidget::PromptType::Alert);
    }
}

//void MainWindow::getCategories()
//{
//    HttpRequest *request = new HttpRequest;
//    //    request->sendRequest(Sort);
//    request->sendRequest("http://api.aixdzs.com/sort");
//    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {

//        ui->lwClassificationView->clear();

//        qDeleteAll(CategoryWidget::Categories);
//        CategoryWidget::Categories.clear();

//        QString jsonData(data);
//        if (success) {
//            QJsonParseError jsonError;
//            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);
//            if (jsonError.error == QJsonParseError::NoError) {
//                QJsonObject jsonObj = jsonDoc.object();

//                // TODO:后台中不要male, 使用categories
//                if (jsonObj.contains("male")) {
//                    QJsonValue jsonValue = jsonObj.value("male");
//                    if (jsonValue.isArray()) {
//                        QJsonArray array = jsonValue.toArray();
//                        int nSize = array.size();
//                        for (int i = 0; i < nSize; ++i) {
//                            QJsonObject obj = array.at(i).toObject();

//                            QString catName = obj.value("name").toString();
//                            int bookCount = obj.value("bookCount").toString().toInt();
//                            int id = obj.value("_id").toString().toInt();

//                            CategoryWidget *cat = new CategoryWidget(catName, bookCount, id, this);
//                            CategoryWidget::Categories.append(cat);

//                            QListWidgetItem *item = new QListWidgetItem(ui->lwClassificationView);
//                            item->setSizeHint(QSize(180, 90));

//                            ui->lwClassificationView->addItem(item);
//                            ui->lwClassificationView->setItemWidget(item, cat);
//                        }
//                    }
//                }
//            }
//        } else {
//            PromptWidget *prompt = new PromptWidget("图书分类信息获取失败，请检查网络", this);
//            prompt->show(PromptWidget::PromptType::Alert);
//        }
//    });
//}
