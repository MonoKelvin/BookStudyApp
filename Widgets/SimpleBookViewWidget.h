#ifndef SIMPLEBOOKVIEWWIDGET_H
#define SIMPLEBOOKVIEWWIDGET_H

#include <QListWidget>

class SimpleBookViewWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SimpleBookViewWidget(QWidget *parent = nullptr);

    void loadLentBooksFromUser(unsigned int id);

    void loadBooksFromLibrary();

signals:

public slots:
};

#endif // SIMPLEBOOKVIEWWIDGET_H
