#ifndef USERPAGEWIDGET_H
#define USERPAGEWIDGET_H

#include <QDialog>

namespace Ui {
class UserPageWidget;
}

class UserPageWidget : public QDialog
{
    Q_OBJECT

public:
    explicit UserPageWidget(QWidget *parent = nullptr);
    ~UserPageWidget();

    void setAvatar(const QPixmap& pixmap);

    void setName(const QString &name);

signals:
    void logout();

private:
    Ui::UserPageWidget *ui;
};

#endif // USERPAGEWIDGET_H
