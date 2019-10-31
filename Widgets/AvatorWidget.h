#ifndef AVATORWIDGET_H
#define AVATORWIDGET_H

#include <QLabel>

class QGraphicsDropShadowEffect;
class QPropertyAnimation;

class AvatorWidget : public QLabel
{
    Q_OBJECT
public:
    explicit AvatorWidget(QWidget *parent = nullptr);

    inline void setAvator(const QPixmap &pixmap)
    {
        mAvator = pixmap;
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

#endif // AVATORWIDGET_H
