#ifndef BOOKSTUDYAPI_H
#define BOOKSTUDYAPI_H

#include <QString>

class BookStudyAPI
{
public:
    BookStudyAPI() {}

    static QString LocalUserDirectory;
    static QString LocalUserCacheDirectory;
    static QString LocalUserLoginDirectory;
    static QString LocalBookCacheDirectory;

    static QString BaseUrl; // http://127.0.0.1/
    static QString Sort; // /sort/
    static QString BookSearch; // /book/search?query={booklencode}
    static QString BookDetail; // /book/{id}

    static QString UserUrl; // /user/{id}
    static QString UserLogInOut;   // /user/login_out.php?
    static QString UserLentBook;    // /user/lent_book.php?
    static QString UserCollection; // /user/collection/id={id}
    static QString UserReadingHistory;  // /user/history/id={id}
};

#endif // BOOKSTUDYAPI_H
