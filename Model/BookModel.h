#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>

class BookModel
{
public:
    BookModel();

    inline int ID(void) const { return mID; }
    inline QString author(void) const { return mAuthor; }
    inline QString coverUrl(void) const { return mCoverUrl; }
    inline QString introduction(void) const { return mIntroduction; }
    inline QString title(void) const { return mTitle; }
    inline QString state(void) const { return mState; }
    inline QString category(void) const { return mCategory; }
    inline int wordCount(void) const { return mWordCount; }
    inline QString updatedTime(void) const { return mUpdatedTime; }
    inline int chaptersCount(void) const { return mChaptersCount; }
    inline QString lastChapter(void) const { return mLastChapter; }

private:
    // 书的ID号
    int mID;

    // 书的作者
    QString mAuthor;

    // 书的封面地址
    QString mCoverUrl;

    // 书的介绍
    QString mIntroduction;

    // 书的标题
    QString mTitle;

    // 书的状态，已完结或者连载
    QString mState;

    // 书的分类
    QString mCategory;

    // 书的字数
    int mWordCount;

    // 书最近更新的时间
    QString mUpdatedTime;

    // 书的章节
    int mChaptersCount;

    // 书最后一章的名字
    QString mLastChapter;
};

#endif // BOOKMODEL_H
