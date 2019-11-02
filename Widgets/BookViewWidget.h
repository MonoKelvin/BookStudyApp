#ifndef BOOKVIEWWIDGET_H
#define BOOKVIEWWIDGET_H

#include <QListWidget>

class BookViewWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit BookViewWidget(QWidget *parent = nullptr);

    void loadLentBooksFromUser(unsigned int id);

signals:

public slots:
    void loadBooksFromLibrary(bool loadMore, const QString& key = "");

private:
    void clearBooks();
};

#endif // BOOKVIEWWIDGET_H
