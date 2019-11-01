﻿#ifndef LOGINWITHQQMAIL_H
#define LOGINWITHQQMAIL_H

#include "ILoginOperation.h"

class LoginWithQQMail : public ILoginOperation
{
    Q_OBJECT

public:
    LoginWithQQMail();

    // ILoginOperation interface
public:
    UserModel *parse(const QString &jsonData) override;
    void verify(const QMap<QString, QString>& mapping) override;
};

#endif // LOGINWITHQQMAIL_H