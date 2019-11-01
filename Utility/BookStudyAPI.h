#ifndef BOOKSTUDYAPI_H
#define BOOKSTUDYAPI_H

#define LocalUserDirectory      QString("/User/")
#define LocalUserCacheDirectory QString(LocalUserDirectory + "Cache/")
#define LocalUserLoginDirectory QString(LocalUserDirectory + "LoginInfo/")
#define LocalBookCacheDirectory QString("/BookCache/");

//#define BaseUrl       "http://api.aixdzs.com";
//#define BaseUrl       "http://localhost:8080";
#define BaseUrl         QString("http://api.bookstudy.com")
#define Sort            QString(BaseUrl + "/sort/")
#define BooksLibrary    QString(BaseUrl + "/book/library.php?first=%1&number=%2")
#define BookSearch      QString(BaseUrl + "/book/search?query=")
#define BookDetail      QString(BaseUrl + "/book/library.php?id=%1")

#define UserUrl             QString(BaseUrl + "/user/index.php?id=")
#define UserLogInOut        QString(BaseUrl + "/user/login_out.php")
#define UserLentBook        QString(BaseUrl + "/user/lent_books.php")
#define UserCollection      QString(BaseUrl + "/user/collection/")
#define UserReadingHistory  QString(BaseUrl + "/user/history/")

/**
 * 每次最多取书的数量
 * @note 当刷新或者加载视图时，需要向服务器请求新的数据，该值就是请求数量的定义
 * @default 默认每次最多取书20本
 */
#define FETCH_BOOK_NUMBER  20

#endif // BOOKSTUDYAPI_H
