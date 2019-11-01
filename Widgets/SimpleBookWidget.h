#ifndef SIMPLEBOOKWIDGET_H
#define SIMPLEBOOKWIDGET_H

#include <QListWidgetItem>

class SimpleBookWidget : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit SimpleBookWidget(QWidget *parent = nullptr);
    SimpleBookWidget(unsigned int id, QWidget *parent = nullptr);

    inline unsigned int id(void) const;
    inline void setID(unsigned int iD);

private:
    unsigned int mID;
};

inline unsigned int SimpleBookWidget::id(void) const
{
    return mID;
}

inline void SimpleBookWidget::setID(unsigned int bookID)
{
    mID = bookID;
}


#endif // SIMPLEBOOKWIDGET_H
