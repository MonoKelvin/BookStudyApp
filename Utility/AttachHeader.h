#ifndef ATTACHHEADER_H
#define ATTACHHEADER_H

#include <QObject>

class AttachHeader : public QObject
{
    Q_OBJECT
public:
    explicit AttachHeader(QObject *parent = nullptr);

    static void attach(const QString& title, QWidget *parent, QWidget *background);
};

#endif // ATTACHHEADER_H
