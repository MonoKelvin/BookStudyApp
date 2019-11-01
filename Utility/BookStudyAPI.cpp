#include "BookStudyAPI.h"

QString BookStudyAPI::LocalUserDirectory = "/User/";
QString BookStudyAPI::LocalUserCacheDirectory = LocalUserDirectory + "Cache/";
QString BookStudyAPI::LocalUserLoginDirectory = LocalUserDirectory + "LoginInfo/";
QString BookStudyAPI::LocalBookCacheDirectory = "/BookCache/";

//QString BookStudyAPI::BaseUrl = "http://api.aixdzs.com";
//QString BookStudyAPI::BaseUrl = "http://localhost:8080";
QString BookStudyAPI::BaseUrl = "http://api.bookstudy.com";
QString BookStudyAPI::Sort = BaseUrl + "/sort/";
QString BookStudyAPI::BookSearch = BaseUrl + "/book/search?query=";
QString BookStudyAPI::BookDetail = BaseUrl + "/book/";

QString BookStudyAPI::UserUrl = BaseUrl + "/user/index.php?id=";
QString BookStudyAPI::UserLogInOut = BaseUrl + "/user/login_out.php";
QString BookStudyAPI::UserCollection = BaseUrl + "/user/collection/";
QString BookStudyAPI::UserLentBook = BaseUrl + "/user/lent_books.php";
QString BookStudyAPI::UserReadingHistory = BaseUrl + "/user/history/";

