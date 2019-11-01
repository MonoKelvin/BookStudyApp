#ifndef BOOKDETAILWIDGET_H
#define BOOKDETAILWIDGET_H

#include <QDialog>

namespace Ui {
class BookDetailWidget;
}

class BookDetailWidget : public QDialog
{
    Q_OBJECT

public:
    explicit BookDetailWidget(unsigned int id, QWidget *parent = nullptr);
    ~BookDetailWidget();

private:
    Ui::BookDetailWidget *ui;

    void loadData(void);

    unsigned int mID;
};

#endif // BOOKDETAILWIDGET_H
