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

        user->setNickName(jsonObj.value("u_name").toString());
        user->setAccount(jsonObj.value("u_account").toString());
        user->setPassward(jsonObj.value("u_password").toString());
        user->setAvatarUrl(jsonObj.value("u_avator").toString());
        user->setID(jsonObj.value("u_id").toInt());
        user->setMD5(jsonObj.value("u_md5").toString());

        return user;
    }

    return nullptr;
}

void LoginWithQQMail::verify(const QMap<QString, QString> &mapping)
{
    HttpRequest *request = new HttpRequest;

    QString postData = "account=" + mapping["account"] + "&password=" + mapping["password"];
    request->sendRequest(BookStudyAPI::UserLogin + "1", HttpRequest::HttpRequestType::POST, postData);

    connect(request, &HttpRequest::request, [=](bool success, const QByteArray &data) {
        if (success) {
            emit login(parse(QString(data)));
        } else {
            emit failed();
        }
    });
}
