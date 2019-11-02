#include "BookWidget.h"

#include "Widgets/BookDetailWidget.h"
#include "Widgets/PromptWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

SimpleBookWidget::SimpleBookWidget(unsigned int id, QWidget *parent)
    : QWidget(parent)
    , mID(id)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(10);
    verticalLayout->setContentsMargins(10, 10, 10, 10);

    mImage = new QLabel(this);
    mImage->setScaledContents(true);
    mImage->setAlignment(Qt::AlignCenter);
    mImage->setObjectName(QString::fromUtf8("lbImage"));
    verticalLayout->addWidget(mImage);

    mTitle = new QLabel(this);
    mTitle->setObjectName(QString::fromUtf8("lbBookTitle"));
    mTitle->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(mTitle);
}

void SimpleBookWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    BookDetailWidget *book = new BookDetailWidget(mID, this);
    connect(book, &BookDetailWidget::loaded, [=](bool success) {
        if (success) {
            book->exec();
        } else {
            PromptWidget *prompt = new PromptWidget("图书信息获取失败，请检查网络", book->parentWidget()->parentWidget());
            prompt->show(PromptWidget::PromptType::Alert);
            book->deleteLater();
        }
    });
}

BookCardWidget::BookCardWidget(unsigned int id, QWidget *parent)
    : QWidget(parent)
    , mID(id)
{
    QGridLayout *gridLayout;

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    mImage = new QLabel(this);
    mImage->setAlignment(Qt::AlignCenter);
    mImage->setObjectName(QString::fromUtf8("lbImage"));
    mImage->setScaledContents(true);
    gridLayout->addWidget(mImage, 0, 0, 4, 1);

    mRating = new QLabel(this);
    mRating->setObjectName(QString::fromUtf8("lbRating"));
    mRating->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    gridLayout->addWidget(mRating, 2, 3, 1, 1);

    mSummary = new QLabel(this);
    mSummary->setObjectName(QString::fromUtf8("lbSummary"));
    mSummary->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    mSummary->setWordWrap(true);
    gridLayout->addWidget(mSummary, 3, 1, 1, 3);

    mAuPubTime = new QLabel(this);
    mAuPubTime->setObjectName(QString::fromUtf8("lbAuPubTime"));
    gridLayout->addWidget(mAuPubTime, 1, 1, 1, 3);

    mTitle = new QLabel(this);
    mTitle->setObjectName(QString::fromUtf8("lbBookTitle"));
    gridLayout->addWidget(mTitle, 0, 1, 1, 3);

    mRatingPgsBar = new QProgressBar(this);
    mRatingPgsBar->setRange(0, 100);
    mRatingPgsBar->setObjectName(QString::fromUtf8("pbRating"));
    mRatingPgsBar->setValue(0);
    gridLayout->addWidget(mRatingPgsBar, 2, 1, 1, 2);

    gridLayout->setRowMinimumHeight(0, 1);
    gridLayout->setRowMinimumHeight(1, 1);
    gridLayout->setRowMinimumHeight(2, 2);
}

void BookCardWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    BookDetailWidget *book = new BookDetailWidget(mID, this);
    connect(book, &BookDetailWidget::loaded, [=](bool success) {
        if (success) {
            book->exec();
        } else {
            PromptWidget *prompt = new PromptWidget("图书信息获取失败，请检查网络", book->parentWidget()->parentWidget());
            prompt->show(PromptWidget::PromptType::Alert);
            book->deleteLater();
        }
    });
}
