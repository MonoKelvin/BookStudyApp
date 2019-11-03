#include "LoginWithQQMail.h"

#include "HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Widgets/PromptWidget.h"

#include <QMap>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

LoginWithQQMail::LoginWithQQMail(QObject *parent)
    : ILoginOperation(parent)
{

}

UserModel* LoginWithQQMail::parse(const QString &jsonData)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);

    if (jsonError.error == QJsonParseError::NoError) {
        QJsonObject jsonObj = jsonDoc.object();
        UserModel *user = new UserModel;

        user->setID(unsigned(jsonObj.value("id").toString().toInt()));
        user->setName(jsonObj.value("name").toString());
        user->setAccount(jsonObj.value("account").toString());
//        user->setPassword(jsonObj.value("password").toString());
        user->setAvatarUrl(jsonObj.value("avatar").toString());
        user->setMD5(jsonObj.value("md5").toString());

        return user;
    }

    return nullptr;
}

void LoginWithQQMail::verify(const QMap<QString, QString> &mapping)
{
    HttpRequest *request = new HttpRequest;

    QString postData = "type=login&account=" + mapping["account"] + "&password=" + mapping["password"];
    request->sendRequest(UserLogInOut, HttpRequest::HttpRequestType::POST, postData);

    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {
        if (success) {
            mUser = QSharedPointer<UserModel>(parse(QString(data)));
            emit logedin();
        } else {
            emit failed("登陆失败，请检查账号或密码的正确！");
        }
    });
}

void LoginWithQQMail::signup(const QMap<QString, QString> &mapping)
{
    HttpRequest *request = new HttpRequest;
    QString postData = "name=" + mapping["name"]
                       + "&account=" + mapping["account"]
                       + "&password=" + mapping["password"];
    request->sendRequest(UserSignup, HttpRequest::HttpRequestType::POST, postData);
    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &jsonData) {
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
        if (jsonError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            if (success) {
                emit registered();
            } else {
                emit failed(jsonObj.value("msg").toString());
            }
        } else {
            emit failed("注册信息不完整！");
        }
    });
}

void LoginWithQQMail::logout()
{
    HttpRequest *request = new HttpRequest;

    // 目前只实现提供id告诉服务器该用户登出了。
    QString postData = QString("type=logout&id=%1").arg(mUser->id());
    request->sendRequest(UserLogInOut, HttpRequest::HttpRequestType::POST, postData);

    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &jsonData) {
        // TODO: 下一个版本加入登录日志，记录登录登出日志，方便维护
        Q_UNUSED(success);
        Q_UNUSED(jsonData);

        // 不管登出失败不失败都发送登出信号
        emit logedout();
    });

    if (!mUser.isNull()) {
        mUser.clear();
        mUser = nullptr;
    }
}
