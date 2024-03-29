﻿#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QVector>

class UserModel
{
    friend class BookStudyAPI;

public:
    UserModel();

    inline QString name(void) const { return mName; }
    inline void setName(const QString &userName) { mName = userName; }
    inline QString account(void) const { return mAccount; }
    inline void setAccount(const QString &account) { mAccount = account; }
    inline QString password(void) const { return mPassword; }
    inline void setPassword(const QString &passward) { mPassword = passward; }
    inline QString avatarUrl(void) const { return mAvatarUrl; }
    inline void setAvatarUrl(const QString &avatarUrl) { mAvatarUrl = avatarUrl; }
    inline unsigned int id(void) const { return mID; }
    inline void setID(unsigned int id) { mID = id; }
    inline QString md5(void) const { return mMD5; }
    inline void setMD5(const QString &md5) { mMD5 = md5; }

private:
    QString mName;
    QString mAccount;
    QString mPassword;
    QString mAvatarUrl;

    /* 用户ID
     * 1. 用于免登录时发送MD5序列查找数据库
     * 2. 方便数据库查找其他内容，而不是使用用户名
     * SELECT user_name FROM UserTable WHERE id = {xxx};
     */
    unsigned int mID;

    /* MD5加密生成的序列号
     * 用于和数据库中第一次保存的MD5序列号进行对比来验证登录。
     * 加密使用的数据：mUserName + mPassward + CurrentTime.ToString => MD5
     */
    QString mMD5;

    // 收藏的书籍，保存的是书的ID号
    QVector<int> mCollection;

    // 看过的书籍，保存的是书的ID号
    QVector<int> mReadingHistory;
};

#endif // USERMODEL_H
