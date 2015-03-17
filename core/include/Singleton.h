#ifndef __SINGLETON_H_
#define __SINGLETON_H_

#include <SmartPtr.h>
#include <NonCopyable.h>

namespace System
{

    template <class T>
    class Singleton : NonCopyable
    {
    private:
        static ReferenceStorage<T>* _self;
    protected:
        virtual ~Singleton() { _self=NULL; }
    public:
        static SmartPtr<T> get();
        void release();
    };

    template <class T>
    ReferenceStorage<T>* Singleton<T>::_self = NULL;

    template <class T>
    SmartPtr<T> Singleton<T>::get()
    {
        if(_self == NULL)
        {
            _self = new ReferenceStorage<T>(new T);
            _self->addRef();
        }

        return SmartPtr<T>(_self);
    }

    template <class T>
    void Singleton<T>::release()
    {
        if (_self && _self->release() == 0)
        {
            delete this;
        }
    }

} // namespace System

#endif /*__SINGLETON_H_*/
