#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QListWidgetItem>

class QLabel;
class QProgressBar;

class SimpleBookWidget : public QListWidgetItem
{
public:
    SimpleBookWidget(unsigned int id, QListWidget *parent);

private:
    unsigned int mID;
};

class BookCardWidget : public QWidget, public QListWidgetItem
{
    Q_OBJECT

    friend class BookViewWidget;
public:
    BookCardWidget(unsigned int id, QWidget *parent);

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
