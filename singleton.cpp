#include "singleton.h"

//C++中类头文件中static为声明静态变量，此处定义，否则编译报错undefined reference to `Singleton::instance'
Singleton *Singleton::instance;
QMutex Singleton::mutex;

Singleton::Singleton()
{

}

Singleton *Singleton::getInstance()
{
    if(instance == nullptr){
        mutex.lock();
        if(instance == nullptr){
            instance = new Singleton();
        }
        mutex.unlock();
    }
    return instance;
}
