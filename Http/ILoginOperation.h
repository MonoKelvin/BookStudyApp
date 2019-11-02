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
    virtual void verify(const QMap<QString, QString> &mapping) = 0;

    /** 注册相关账号，可以用该账号进行登录
     * @param mapping : 注册时提供的数据键值对
     * 一般为：
     *      "name" : "username"
     *      "account" : "123465@qq.com"
     *      "password" : "pwd123"
     * @note 该方法不是必须继承实现的
     */
    virtual void signup(const QMap<QString, QString> &) {}

signals:
    // 信号：登录成功
    void login(UserModel *user);

    // 信号：注册账号成功
    void registered();

    // 信号：登陆或注册失败，返回失败消息
    void failed(const QString& message = "");

    // 信号：注销
    void logout();
};

#endif // ILOGINOPERATION_H

