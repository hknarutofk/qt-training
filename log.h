#ifndef LOG_H
#define LOG_H
#include <QDebug>
#define logDebug() qDebug() << __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"

#endif // LOG_H
