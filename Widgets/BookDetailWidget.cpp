#include "BookDetailWidget.h"
#include "ui_BookDetailWidget.h"

#include "Http/HttpRequest.h"
#include "Utility/BookStudyAPI.h"
#include "Utility/Utility.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QProgressBar>
#include <QPushButton>

BookDetailWidget::BookDetailWidget(unsigned int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetailWidget),
    mID(id)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 布局
    ui->sawBookContents->layout()->setContentsMargins(SHADOW_PADDING, HEADER_HEIGHT + 40, SHADOW_PADDING, SHADOW_PADDING);

    // 窗口标题
    QLabel * lbHeader = new QLabel("书籍详情", this);
    lbHeader->setObjectName(QString::fromUtf8("lbHeader_h2"));
    lbHeader->setAlignment(Qt::AlignCenter);
    lbHeader->setGeometry(SHADOW_PADDING, SHADOW_PADDING, width() - 2 * SHADOW_PADDING, HEADER_HEIGHT);

    // 窗口的关闭按钮
    QPushButton * btnClose = new QPushButton("×", this);
    btnClose->setObjectName(QString::fromUtf8("btnClose"));
    btnClose->setGeometry(width() - HEADER_HEIGHT - SHADOW_PADDING, SHADOW_PADDING, HEADER_HEIGHT, HEADER_HEIGHT);
    btnClose->raise();

    // 关闭事件
    connect(btnClose, &QPushButton::clicked, this, &BookDetailWidget::close);

    // 设置美化特效
    setShadowEffect(this, QColor(160, 165, 170, 100), qreal(SHADOW_PADDING));
    setShadowEffect(lbHeader, QColor(200, 210, 220, 80), 30.0, 0.0, 4.0);
    setShadowEffect(ui->lbRemaining_h2, QColor(255, 164, 39, 140), 16.0, 0.0, 4.0);

    // 加载数据
    loadData();
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
            success = false;

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
                    ui->lbRating_h2->setText(QString::number(rating, 'f', 1) + "分");
                    ui->lbRatingPgsBar->setValue(int(rating * 10));

                    // 处各种信息
                    QString author = obj.value("author").toString();
                    QString pubTime = obj.value("pubdate").toString();
                    QString collection = obj.value("remaining").toString();
                    QString originTitle = obj.value("origin_title").toString();
                    QString translator = obj.value("translator").toString();
                    QString tags = obj.value("tags").toString();
                    QString binding = obj.value("binding").toString();
                    QString publisher = obj.value("publisher").toString();

                    author = (author.isEmpty()) ? "不详" : author;
                    pubTime = (pubTime.isEmpty()) ? "不详" : pubTime;
                    collection = (collection.toInt() == 0) ? "暂无书源" : ("馆藏：" + collection + "本");
                    tags = (tags.isEmpty()) ? "无" : tags;
                    translator = (translator.isEmpty()) ? "不详" : translator;
                    binding = (binding.isEmpty()) ? "不详" : binding;
                    publisher = (publisher.isEmpty()) ? "不详" : publisher;
                    originTitle = (originTitle.isEmpty()) ? "无" : originTitle;

                    ui->lbAuthor->setText("作者：" + author);
                    ui->lbSubTitle->setText("副标题：" + obj.value("subtitle").toString());
                    ui->lbPublisher->setText("出版社：" + publisher);
                    ui->lbPubdate->setText("出版时间：" + pubTime);
                    ui->lbPage->setText("页数：" + obj.value("pages").toString());
                    ui->lbPrice->setText("定价：" + obj.value("price").toString());
                    ui->lbISBN13->setText("IBSN13：" + obj.value("isbn13").toString());
                    ui->lbSummary->setText(obj.value("summary").toString());
                    ui->lbAuthorIntro->setText(obj.value("author_intro").toString());
                    ui->lbCatalog->setText(obj.value("catalog").toString());
                    ui->lbBinding->setText(binding);
                    ui->lbOriginTitle->setText(originTitle);
                    ui->lbTags->setText(tags);
                    ui->lbTranslator->setText(translator);
                    ui->lbRemaining_h2->setText(collection);

                    // 请求封面
                    HttpRequest *imgRequest = new HttpRequest;
                    imgRequest->sendRequest(obj.value("image").toString());
                    connect(imgRequest, &HttpRequest::request, [ = ](bool suc, const QByteArray &data) {
                        if (suc) {
                            QPixmap pixmap;
                            if (pixmap.loadFromData(data)) {
                               ui->lbImage->setPixmap(pixmap);
                            }
                        }
                    });

                    success = true;
                }
            }
        }

        if (!success) {
            emit loaded(false);
        } else {
            emit loaded(true);
        }
    });
}
