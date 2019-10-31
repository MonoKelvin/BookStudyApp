#include "LoginWithGithub.h"
#include "Model/UserModel.h"

#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

LoginWithGithub::LoginWithGithub()
{

}


void LoginWithGithub::parse(const QString &jsonData)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError) {
        QJsonObject jsonObj = jsonDoc.object();
        int nSize = jsonObj.size();
        for (int i = 0; i < nSize; ++i) {
            mCurrentUser->setUserName(jsonObj.value("login").toString());
            mCurrentUser->setAvatarUrl(jsonObj.value("avatar_url").toString());
            mCurrentUser->setID(jsonObj.value("id").toInt());
        }

        emit login();
    } else {
        // TODO:报错
    }
}
