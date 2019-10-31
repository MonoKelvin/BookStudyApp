#ifndef ILOGINOPERATION_H
#define ILOGINOPERATION_H

#include "Model/UserModel.h"

#include <QObject>
#include <QString>

class ILoginOperation : public QObject
{
    Q_OBJECT
public:
    virtual ~ILoginOperation() {}

    /* 解析登录时请求返回的json数据
     * @return UserModel* : 解析成功返回用户对像模型，解析失败返回nullptr
     */
    virtual UserModel *parse(const QString &jsonData) = 0;

    /* 发起网络请求，验证是否登录成功
     * @param mapping : 验证的数据键值对
     * 比如："account":"user1","password":"1234"
     * 或者："md5":"f2d2b9ae2d741a04634adfe18e2ea2c0"
     */
    virtual void verify(const QMap<QString, QString>& mapping) = 0;

signals:
    // 信号：登录成功
    void login(UserModel *user);

    // 信号：登陆失败
    void failed();

    // 信号：注销
    void logout();
};

#endif // ILOGINOPERATION_H

