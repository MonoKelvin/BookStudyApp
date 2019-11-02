#include "BookViewWidget.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Widgets/PromptWidget.h"
#include "Widgets/BookWidget.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QProgressBar>

BookViewWidget::BookViewWidget(QWidget *parent)
    : QListWidget(parent)
{

}

void BookViewWidget::loadLentBooksFromUser(unsigned int id)
{
    HttpRequest *request = new HttpRequest;
    QString postData = QString("id=%1").arg(id);
    request->sendRequest(UserLentBook, HttpRequest::HttpRequestType::POST, postData);

    connect(request, &HttpRequest::request, [=](bool success, const QString &jsonData) {
        if (success) {
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);

            if (jsonError.error == QJsonParseError::NoError) {
                if (jsonDoc.isArray()) {
                    // 获取书籍数组列表
                    QJsonArray jsonArr = jsonDoc.array();
                    for (auto iter = jsonArr.begin(); iter != jsonArr.end(); iter++) {
                        auto obj = (*iter).toObject();

                        // 新建书籍类
                        SimpleBookWidget *book = new SimpleBookWidget(unsigned(obj.value("id").toString().toInt()), this);
                        book->setText(obj.value("title").toString());
                        book->setIcon(QIcon(QPixmap("qrc:/Icons/AppIcons/default_book.png")));

                        // 请求封面
                        HttpRequest *imgRequest = new HttpRequest;
                        imgRequest->sendRequest(obj.value("image").toString());
                        connect(imgRequest, &HttpRequest::request, [ book ](bool success, const QByteArray &data) {
                            if (success) {
                                QPixmap pixmap;
                                if (pixmap.loadFromData(data)) {
                                    book->setIcon(QIcon(pixmap));
                                }
                            }
                        });

                        // 放到列表中
                        this->addItem(book);
                    }
                }
            }

        } else {
            PromptWidget *prompt = new PromptWidget("借书列表获取失败，请检查网络", this);
            prompt->show(PromptWidget::PromptType::Alert);
        }
    });
}

void BookViewWidget::loadBooksFromLibrary()
{
    this->scrollToBottom();

    HttpRequest *request = new HttpRequest;
    request->sendRequest(BooksLibrary.arg(this->count()).arg(FETCH_BOOK_NUMBER));

    connect(request, &HttpRequest::request, [=](bool success, const QString &jsonData) {
        if (success) {
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);

            if (jsonError.error == QJsonParseError::NoError) {
                if (jsonDoc.isArray()) {
                    // 获取书籍数组列表
                    QJsonArray jsonArr = jsonDoc.array();
                    for (auto iter = jsonArr.begin(); iter != jsonArr.end(); iter++) {
                        auto obj = (*iter).toObject();

                        // 新建书籍类
                        BookCardWidget *book = new BookCardWidget(unsigned(obj.value("id").toString().toInt()), this);
                        book->mTitle->setText(obj.value("title").toString());
                        book->mImage->setPixmap(QPixmap("qrc:/Icons/AppIcons/default_book.png"));

                        // 设置评分
                        double rating = obj.value("rating").toString().toDouble();
                        book->mRating->setText(QString::number(rating, 'f', 1) + "分");
                        book->mRatingPgsBar->setValue(int(rating * 10));

                        // 处理简介的换行和省略号
                        QString summary = obj.value("summary").toString().replace('\n',"");
                        QFontMetrics fontWidth(book->mSummary->font());
                        QString elideNote = fontWidth.elidedText(summary, Qt::ElideRight, 800);
                        book->mSummary->setText(elideNote);
                        book->mSummary->setToolTip(summary.left(100) + QString(" ..."));

                        // 处理作者 + 出版时间 + 馆藏数量等
                        QString author = obj.value("author").toString();
                        QString pubTime = obj.value("pubdate").toString();
                        QString collection = obj.value("remaining").toString();
                        author = (author.isEmpty()) ? "" : author + " / ";
                        pubTime = (pubTime.isEmpty()) ? "" : pubTime + " / ";
                        collection = (collection.toInt() == 0) ? "暂无图书可借" : ("馆藏：" + collection + "本");
                        book->mAuPubTime->setText(author + pubTime + collection);

                        // 请求封面
                        HttpRequest *imgRequest = new HttpRequest;
                        imgRequest->sendRequest(obj.value("image").toString());
                        connect(imgRequest, &HttpRequest::request, [ book ](bool success, const QByteArray &data) {
                            if (success) {
                                QPixmap pixmap;
                                if (pixmap.loadFromData(data)) {
                                    book->mImage->setPixmap(pixmap);
                                }
                            }
                        });

                        // 放到列表中
                        QListWidgetItem *item = new QListWidgetItem();
                        this->addItem(item);
                        this->setItemWidget(item, book);
                    }
                }
            }

        } else {
            PromptWidget *prompt = new PromptWidget("图书获取失败，请检查网络", this);
            prompt->show(PromptWidget::PromptType::Alert);
        }
    });
}
