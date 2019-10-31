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

    void setAvator(const QPixmap& pixmap);

    void setNickName(const QString &nickName);

private:
    Ui::UserPageWidget *ui;
};

#endif // USERPAGEWIDGET_H
