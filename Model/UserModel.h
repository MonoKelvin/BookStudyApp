#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QVector>

class UserModel
{
    friend class BookStudyAPI;

public:
    UserModel();

    inline QString nickName(void) const { return mNickName; }
    inline void setNickName(const QString &userName) { mNickName = userName; }
    inline QString account(void) const { return mAccount; }
    inline void setAccount(const QString &account) { mAccount = account; }
    inline QString passward(void) const { return mPassward; }
    inline void setPassward(const QString &passward) { mPassward = passward; }
    inline QString avatarUrl(void) const { return mAvatarUrl; }
    inline void setAvatarUrl(const QString &avatarUrl) { mAvatarUrl = avatarUrl; }
    inline int id(void) const { return mID; }
    inline void setID(int id) { mID = id; }
    inline QString md5(void) const { return mMD5; }
    inline void setMD5(const QString &md5) { mMD5 = md5; }

private:
    QString mNickName;
    QString mAccount;
    QString mPassward;
    QString mAvatarUrl;

    /* 用户ID
     * 1. 用于免登录时发送MD5序列查找数据库
     * 2. 方便数据库查找其他内容，而不是使用用户名
     * SELECT user_name FROM UserTable WHERE id = {xxx};
     */
    int mID;

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
