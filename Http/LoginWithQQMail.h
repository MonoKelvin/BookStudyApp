#ifndef LOGINWITHQQMAIL_H
#define LOGINWITHQQMAIL_H

#include "ILoginOperation.h"

class LoginWithQQMail : public ILoginOperation
{
    Q_OBJECT
public:
    LoginWithQQMail(QObject *parent = nullptr);

    // ILoginOperation interface
public:
    UserModel *parse(const QString &jsonData) override;
    void verify(const QMap<QString, QString>& mapping) override;
    void signup(const QMap<QString, QString> &mapping) override;

    // ILoginOperation interface
public slots:
    void logout() override;

};

#endif // LOGINWITHQQMAIL_H
