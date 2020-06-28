#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

class Singleton : public QObject
{
    Q_OBJECT
public:
    explicit Singleton(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SINGLETON_H
