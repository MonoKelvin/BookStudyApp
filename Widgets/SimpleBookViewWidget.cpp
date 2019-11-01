#include "SimpleBookViewWidget.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Widgets/PromptWidget.h"
#include "Widgets/SimpleBookWidget.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

SimpleBookViewWidget::SimpleBookViewWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &SimpleBookViewWidget::itemDoubleClicked, [=](QListWidgetItem *item) {
        SimpleBookWidget *book = static_cast<SimpleBookWidget *>(item);
        // TODO: 获取book的详情
    });
}

void SimpleBookViewWidget::loadLentBooksFromUser(unsigned int id)
{
    HttpRequest *request = new HttpRequest;
    QString postData = QString("id=%1").arg(id);
    request->sendRequest(BookStudyAPI::UserLentBook, HttpRequest::HttpRequestType::POST, postData);

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
