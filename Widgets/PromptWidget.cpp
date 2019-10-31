#include "PromptWidget.h"

#include "Utility/Utility.h"

#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>


PromptWidget::PromptWidget(const QString &prompt, QWidget *parent)
    : QWidget(parent)
{
    this->resize(20 * prompt.length(), 5 * prompt.length());

    QLabel *lbContents = new QLabel(prompt, this);
    QHBoxLayout *hbLayout = new QHBoxLayout(this);

    lbContents->setAlignment(Qt::AlignCenter);
    lbContents->setWordWrap(true);

    hbLayout->addWidget(lbContents);
    hbLayout->setMargin(10);

    this->setLayout(hbLayout);
//    setShadowEffect(this, QColor(100, 100, 100, 160), 30.0);
}

void PromptWidget::show(PromptWidget::PromptType type)
{
    if (type == PromptType::Prompt) {
        setStyleSheet("background: rgb(85,118,189); color: white; border-radius: 4px;");
    } else {
        setStyleSheet("background: rgb(220,50,120); color: white; border-radius: 4px;");
    }

    QSize pwSize = parentWidget()->size();
    int xOffset = (pwSize.width() - this->width()) / 2;
    QRect oriRect = QRect(xOffset, pwSize.height() + 10, this->width(), this->height());

    QPropertyAnimation *showAni = new QPropertyAnimation(this, "geometry", this);
    showAni->setDuration(300);
    showAni->setStartValue(oriRect);
    int yOffset = this->height() + 20;
    oriRect.setTop(oriRect.top() - yOffset);
    oriRect.setBottom(oriRect.bottom() - yOffset);
    showAni->setEndValue(oriRect);
    showAni->setEasingCurve(QEasingCurve::OutBack);

    QPropertyAnimation *quitAni = new QPropertyAnimation(this, "geometry", this);
    quitAni->setDuration(300);
    quitAni->setStartValue(showAni->endValue());
    quitAni->setEndValue(showAni->startValue());
    quitAni->setEasingCurve(QEasingCurve::InBack);

    QSequentialAnimationGroup *seqAnimation = new QSequentialAnimationGroup(this);

    seqAnimation->addAnimation(showAni);
    seqAnimation->addPause(3000);
    seqAnimation->addAnimation(quitAni);
    seqAnimation->setLoopCount(1);

    seqAnimation->start();
    connect(seqAnimation, &QSequentialAnimationGroup::finished, this, &PromptWidget::deleteLater);
    QWidget::show();
}
