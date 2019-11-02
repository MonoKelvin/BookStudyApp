#include "BookDetailWidget.h"
#include "ui_BookDetailWidget.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Utility/Utility.h"
#include "Widgets/PromptWidget.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QProgressBar>

BookDetailWidget::BookDetailWidget(unsigned int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetailWidget),
    mID(id)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    loadData();

    setShadowEffect(this, QColor(180, 180, 190, 220), 30.0, 0.0, 4.0);
}

BookDetailWidget::~BookDetailWidget()
{
    delete ui;
}

void BookDetailWidget::loadData()
{
    HttpRequest *request = new HttpRequest;
    request->sendRequest(BookDetail.arg(mID));

    connect(request, &HttpRequest::request, [=](bool success, const QString &jsonData) {
        if (success) {
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &jsonError);

            if (jsonError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    // 获取书籍数组列表
                    auto obj = jsonDoc.object();
                    // 新建书籍类
                    ui->lbBookTitle->setText(obj.value("title").toString());
                    ui->lbImage->setPixmap(QPixmap("qrc:/Icons/AppIcons/default_book.png"));

                    // 设置评分
                    double rating = obj.value("rating").toString().toDouble();
                    ui->lbRating->setText(QString::number(rating, 'f', 1) + "分");
                    ui->lbRatingPgsBar_dtl->setValue(int(rating * 10));

                    // 处理作者 + 出版时间 + 馆藏数量等
                    QString author = obj.value("author").toString();
                    QString pubTime = obj.value("pubdate").toString();
                    QString collection = obj.value("remaining").toString();
                    author = (author.isEmpty()) ? "" : author + "作者不详";
                    pubTime = (pubTime.isEmpty()) ? "" : pubTime + "出版时间不详";
                    collection = (collection.toInt() == 0) ? "暂无图书可借" : ("馆藏：" + collection + "本");

                    ui->lbAuthor->setText("作者：" + author);
                    ui->lbPubdate->setText("出版时间：" + pubTime);
                    ui->lbSubTitle->setText("副标题：" + obj.value("subtitle").toString());
                    ui->lbBinding->setText(obj.value("binding").toString());
                    ui->lbPage->setText(obj.value("pages").toString());
                    ui->lbPrice->setText(obj.value("prices").toString());
                    ui->lbOriginTitle->setText(obj.value("origin_title").toString());
                    ui->lbTags->setText(obj.value("tags").toString());
                    ui->lbTranslator->setText(obj.value("translator").toString());

                    // 处理简介的换行和省略号
                    ui->lbSummary->setText(obj.value("summary").toString());
                    ui->lbAuthorIntro->setText(obj.value("author_intro").toString());
                    ui->lbCatalog->setText(obj.value("catalog").toString());

                    // 请求封面
                    HttpRequest *imgRequest = new HttpRequest;
                    imgRequest->sendRequest(obj.value("image").toString());
                    connect(imgRequest, &HttpRequest::request, [ = ](bool success, const QByteArray &data) {
                        if (success) {
                            QPixmap pixmap;
                            if (pixmap.loadFromData(data)) {
                               ui->lbImage->setPixmap(pixmap);
                            }
                        }
                    });
                }
            }

        } else {
            PromptWidget *prompt = new PromptWidget("图书获取失败，请检查网络", this);
            prompt->show(PromptWidget::PromptType::Alert);
        }
    });
}
