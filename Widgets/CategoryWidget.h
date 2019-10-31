#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include <QWidget>

namespace Ui {
class CategoryWidget;
}

class CategoryWidget : public QWidget
{
    Q_OBJECT

    friend class BookStudyAPI;

public:
    CategoryWidget(const QString &categoryName, int bookCount, int id, QWidget *parent = nullptr);
    ~CategoryWidget();

    static QVector<CategoryWidget *> Categories;

    inline QString getCategoryName();
    inline int getBookCount();

    inline int getCategoryID(void) const;
    inline void setCategoryID(int categoryID);

private:
    Ui::CategoryWidget *ui;

    int mCategoryID;
};

#endif // CATEGORYWIDGET_H
