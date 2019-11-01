#include "LoginWithQQMail.h"

#include "HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Widgets/PromptWidget.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>


LoginWithQQMail::LoginWithQQMail()
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
        user->setNickName(jsonObj.value("name").toString());
//        user->setAccount(jsonObj.value("account").toString());
//        user->setPassward(jsonObj.value("password").toString());
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
            emit login(parse(QString(data)));
        } else {
            emit failed();
        }
    });
}
