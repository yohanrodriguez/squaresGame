#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

template <typename T>
class Singleton {
protected:
    Singleton () {}
    virtual ~Singleton () {}

public:
    static T *singleton() {
        if(NULL == _singleton) _singleton = new T;
        return (static_cast<T*> (_singleton));
    }

    static void kill() {
        if(NULL != _singleton) {
            delete _singleton;
            _singleton = NULL;
        }
    }

private:
    static T *_singleton;
};

template <class T> T* Singleton<T>::_singleton=NULL;

#endif // SINGLETON_H
