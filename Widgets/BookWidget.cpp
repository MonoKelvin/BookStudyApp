#include "BookWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

SimpleBookWidget::SimpleBookWidget(unsigned int id, QListWidget *parent)
    : QListWidgetItem(parent)
    , mID(id)
{

}

BookCardWidget::BookCardWidget(unsigned int id, QWidget *parent)
    : QWidget(parent)
    , mID(id)
{
    QGridLayout *gridLayout;

    resize(480, 180);
    setMaximumSize(480, 180);
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    mImage = new QLabel(this);
    mImage->setMaximumWidth(130);
    mImage->setScaledContents(true);
    gridLayout->addWidget(mImage, 0, 0, 4, 1);

    mRating = new QLabel(this);
    mRating->setObjectName(QString::fromUtf8("lbRating_lib"));
    mRating->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    gridLayout->addWidget(mRating, 2, 3, 1, 1);

    mSummary = new QLabel(this);
    mSummary->setObjectName(QString::fromUtf8("lbSummary_lib"));
    mSummary->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    mSummary->setWordWrap(true);
    gridLayout->addWidget(mSummary, 3, 1, 1, 3);

    mAuPubTime = new QLabel(this);
    mAuPubTime->setObjectName(QString::fromUtf8("lbAuPubTime_lib"));
    gridLayout->addWidget(mAuPubTime, 1, 1, 1, 3);

    mTitle = new QLabel(this);
    mTitle->setObjectName(QString::fromUtf8("lbBookTitle_lib"));
    mTitle->setMinimumSize(QSize(0, 30));
    gridLayout->addWidget(mTitle, 0, 1, 1, 3);

    mRatingPgsBar = new QProgressBar(this);
    mRatingPgsBar->setRange(0, 100);
//    mRatingPgsBar->setObjectName(QString::fromUtf8("pbRating_lib"));
    mRatingPgsBar->setValue(24);
    gridLayout->addWidget(mRatingPgsBar, 2, 1, 1, 2);

    gridLayout->setRowMinimumHeight(0, 1);
    gridLayout->setRowMinimumHeight(1, 1);
    gridLayout->setRowMinimumHeight(2, 2);

}
