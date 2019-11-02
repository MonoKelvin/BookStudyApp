#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QListWidgetItem>

class QLabel;
class QProgressBar;

class SimpleBookWidget : public QWidget
{
    Q_OBJECT

    friend class BookViewWidget;
public:
    SimpleBookWidget(unsigned int id, QWidget *parent);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *mImage;
    QLabel *mTitle;
    unsigned int mID;
};

class BookCardWidget : public QWidget
{
    Q_OBJECT

    friend class BookViewWidget;
public:
    BookCardWidget(unsigned int id, QWidget *parent);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *mImage;
    QLabel *mTitle;
    QLabel *mAuPubTime;
    QLabel *mRating;
    QProgressBar *mRatingPgsBar;
    QLabel *mSummary;
    unsigned int mID;
};

#endif // BOOKWIDGET_H
