#ifndef SINGLETON_H
#define SINGLETON_H

#include <QSharedPointer>
#include <QMutex>

/**
 * 单例模板类，要实现单例的子类继承即可
 */
template<class T>
class Singleton
{
public:
    static T *getInstance()
    {
        if (m_pInstance == nullptr)
        {
            QMutexLocker mutexLocker(&mMutex);
            if (m_pInstance == nullptr) {
                m_pInstance = new T();
            }
        }
        return m_pInstance;
    }

    // 将默认的构造函数删除
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() = default;

    class SingletonGC
    {
    public:
        ~SingletonGC()
        {
            if (m_pInstance)
            {
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };

private:
    // 创建互斥锁，防止多线程构造实例时的问题
    static QMutex mMutex;

    // 单例对象
    static T *m_pInstance;

    // 内存回收对象
    static SingletonGC mGC;
};

template <class T>
T *Singleton<T>::m_pInstance = nullptr;

template <class T>
QMutex Singleton<T>::mMutex;

template <class T>
typename Singleton<T>::SingletonGC Singleton<T>::mGC;

#endif // SINGLETON_H
