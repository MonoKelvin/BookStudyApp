#ifndef UTILITY_H
#define UTILITY_H

#include <QWidget>

#define BS_MAJOR_VERSION 1
#define BS_MINOR_VERSION 0
#define BS_REVERSION     0

// 最多可收藏书的数量
#define MAX_COLLECTION_COUNT    1024

// 最多保存的阅读记录
#define MAX_READING_HISTORY     1024

extern void setShadowEffect(QWidget *widget, const QColor &color, qreal radius = 20.0, qreal xoffset = 0.0, qreal yoffset = 0.0);

#endif // UTILITY_H
