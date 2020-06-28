#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QMutex>

class Singleton : public QObject
{
    Q_OBJECT
public:
    static Singleton *getInstance();

private:
    static Singleton *instance;
    static QMutex mutex;
    Singleton();

signals:

public slots:
};

#endif // SINGLETON_H
