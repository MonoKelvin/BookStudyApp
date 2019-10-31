#include "BookStudyAPI.h"

QString BookStudyAPI::LocalUserDirectory = "./User/";
QString BookStudyAPI::LocalUserCacheDirectory = LocalUserDirectory + "Cache/";
QString BookStudyAPI::LocalUserLoginDirectory = LocalUserDirectory + "LoginInfo/";
QString BookStudyAPI::LocalBookCacheDirectory = "./BookCache/";

//QString BookStudyAPI::BaseUrl = "http://api.aixdzs.com";
//QString BookStudyAPI::BaseUrl = "http://localhost:8080";
QString BookStudyAPI::BaseUrl = "http://bookstudy.com";
QString BookStudyAPI::Sort = BaseUrl + "/sort/";
QString BookStudyAPI::BookSearch = BaseUrl + "/book/search?query=";
QString BookStudyAPI::BookDetail = BaseUrl + "/book/";

QString BookStudyAPI::UserUrl = BaseUrl + "/user/index.php?id=";
QString BookStudyAPI::UserLogin = BaseUrl + "/user/login.php?";
QString BookStudyAPI::UserCollection = BaseUrl + "/user/collection/";
QString BookStudyAPI::UserReadingHistory = BaseUrl + "/user/history/";

