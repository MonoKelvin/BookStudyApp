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
#include <QPushButton>

BookDetailWidget::BookDetailWidget(unsigned int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetailWidget),
    mID(id)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    int hdHeight = 50;
    int padding = 30;

    // 布局
    ui->sawBookContents->layout()->setContentsMargins(padding, hdHeight + 20, padding, padding);

    // 窗口标题
    QLabel *lbHeader = new QLabel("书籍详情", this);
    lbHeader->setObjectName(QString::fromUtf8("lbHeader_h2"));
    lbHeader->setAlignment(Qt::AlignCenter);
    lbHeader->setGeometry(padding, padding, width() - 2 * padding, hdHeight);

    // 窗口的关闭按钮
    QPushButton *btnClose = new QPushButton("×", this);
    btnClose->setObjectName(QString::fromUtf8("btnCloseBtn"));
    btnClose->setGeometry(width() - hdHeight - padding, padding, hdHeight, hdHeight);
    btnClose->raise();

    // 关闭事件
    connect(btnClose, &QPushButton::clicked, this, &BookDetailWidget::close);

    // 设置美化特效
    setShadowEffect(this, QColor(160, 165, 170, 140), qreal(padding));
    setShadowEffect(ui->lbRemaining_h2, QColor(255, 164, 39, 140), 16.0, 0.0, 4.0);
    setShadowEffect(lbHeader, QColor(200, 210, 220, 100), 20.0, 0.0, 4.0);

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
                    ui->lbRatingPgsBar_dtl->setValue(int(rating * 10));

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
