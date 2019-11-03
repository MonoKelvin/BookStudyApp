#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QLabel>

class AvatarWidget : public QLabel
{
    Q_OBJECT
public:
    explicit AvatarWidget(QWidget *parent = nullptr);

    inline void setAvatar(const QPixmap &pixmap)
    {
        mAvator = pixmap;
        update();
    }

    inline void setDefaultAvatar()
    {
        mAvator = QPixmap("qrc:/Icon/AppIcons/default_avatar.png");
        update();
    }

    inline QPixmap avator() const
    {
        return mAvator;
    }

signals:
    void onClick(void);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap mAvator;
};

#endif // AVATARWIDGET_H
