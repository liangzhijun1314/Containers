/*******************************************************************************
** @file:     singleton.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-7-23
** @version:
*******************************************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H
#include <thread>
#include <mutex>
using namespace std;

template<typename T>
class Singleton
{
public:
    template<typename... Args>
    static T* instance(Args&&... arg)
    {
        try {
            static std::mutex mutex;
            std::lock_guard<std::mutex> glock(mutex);
            if (nullptr == m_instance)
            {
                m_instance = new T(std::forward<Args>(arg)...);
            }
        } catch(...) {

        }

        return m_instance;
    }

    static void freeinstance()
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> glock(mutex);
        if (nullptr != m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    virtual void init() = 0;
    virtual void clear() = 0;

private:
    static T* m_instance;
};

/*
 *  在类外定义成员函数，若此成员函数中有模板参数存在，则除了需要和一般类的类外定义成员函数一样的定义外，
 *  还需要在函数外进行模板声明 template<class T>
 */
template<typename T>
T* Singleton<T>::m_instance = nullptr;

/*
 *  这边比较难理解的就是：为什么要声明友元类？
 *  在于Singleton<Obj>::instance()需要去new Obj要访问到构造函数，如果构造函数是private则访问不了，
 *  声明为友元，可以完全访问
 */
#define DECLARE_SINGLETON(Obj) \
friend class Singleton<Obj>; \
public: \
static Obj *instance() \
{ \
return Singleton<Obj>::instance(); \
} \
static void freeinstance() \
{ \
Singleton<Obj>::freeinstance();  \
}

#define SINGLETON_INIT(Class) \
public:\
Class(){ init(); }\
virtual ~Class(){ clear(); }\
protected:\
virtual void init();\
virtual void clear();

#endif // SINGLETON_H
