#ifndef LOGINWITHGITHUB_H
#define LOGINWITHGITHUB_H

#include "ILoginOperation.h"

class LoginWithGithub : public ILoginOperation
{
    Q_OBJECT
public:
    LoginWithGithub();

    UserModel *parse(const QString &jsonData) override;
};

#endif // LOGINWITHGITHUB_H
