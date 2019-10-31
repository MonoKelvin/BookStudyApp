#include "CategoryWidget.h"
#include "ui_CategoryWidget.h"

QVector<CategoryWidget *> CategoryWidget::Categories;

CategoryWidget::CategoryWidget(const QString &categoryName, int bookCount, int id, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CategoryWidget)
{
    ui->setupUi(this);
    setCursor(Qt::PointingHandCursor);

    ui->lbCategoryName->setText(categoryName);
    ui->lbBookCount->setText(QString::asprintf("%d本书", bookCount));
    mCategoryID = id;
}

CategoryWidget::~CategoryWidget()
{
    delete ui;
}

QString CategoryWidget::getCategoryName()
{
    return ui->lbCategoryName->text();
}

int CategoryWidget::getBookCount()
{
    int size = ui->lbBookCount->text().size();
    return ui->lbBookCount->text().left(size - 2).toInt();
}

int CategoryWidget::getCategoryID(void) const
{
    return mCategoryID;
}

void CategoryWidget::setCategoryID(int categoryID)
{
    mCategoryID = categoryID;
}
