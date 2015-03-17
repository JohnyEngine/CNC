#ifndef _SMARTPTR_H_
#define _SMARTPTR_H_

#include <stdlib.h>

namespace System
{

    template < typename D, typename S >
    void check_convertible()
    {
        D* p = static_cast< S* >( NULL );
        (void)p;
    }

    class ReferenceCounter
    {
    private:
        unsigned int mCount; // Reference count

    public:

        ReferenceCounter()
            : mCount(0)
        {
        }

        void addRef()
        {
            // Increment the reference count
            mCount++;
        }

        unsigned int release()
        {
            // Decrement the reference count and
            // return the reference count.
            return --mCount;
        }

        unsigned int getCount() const
        {
            return mCount;
        }
    };

    template < typename T >
    class ReferenceStorage : public ReferenceCounter
    {
    private:
        T* mReference; // Reference
        ReferenceCounter mWeakCounter;

    public:

        ReferenceStorage(T* aReference)
            : mReference(aReference)
        {
        }

        ~ReferenceStorage()
        {
            if (mReference)
            {
                checkedDelete(mReference);
            }
        }
    
        T* getImpl()
        {
            return mReference;
        }

        void setImpl(T* p)
        {
            mReference = p;
        }

        unsigned int release()
        {
            unsigned int count = ReferenceCounter::release();

            if (mReference && count == 0)
            {
                checkedDelete(mReference);

                mReference = NULL;
            }

            return count;
        }

        template < typename D >
        ReferenceStorage<D>* staticCast()
        {
            check_convertible<D, T>();

            return static_cast<ReferenceStorage<D>*>(static_cast<void*>(this));
        }

        void checkedDelete(T* p)
        {
            typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
            (void) sizeof(type_must_be_complete);

            delete p;
        }

        void addWeakRef()
        {
            mWeakCounter.addRef();
        }

        unsigned int releaseWeak()
        {
            return mWeakCounter.release();
        }

        unsigned int getWeakCount() const
        {
            return mWeakCounter.getCount();
        }
    };

    template < typename T >
    class SmartPtr
    {
        template < typename T > friend class WeakPtr;

    private:
        ReferenceStorage<T>* mStorage;      

    public:

        SmartPtr()
            : mStorage(NULL)
        {}

        SmartPtr(T* p) 
            : mStorage(NULL)
        {
            if (p)
            {
                mStorage = new ReferenceStorage<T>(p);

                mStorage->addRef();
            }
        }

        SmartPtr(const SmartPtr <T> & p)
            : mStorage(p.mStorage)
        {
            if (mStorage)
            {
                mStorage->addRef();
            }
        }

        template < typename S >
        SmartPtr(ReferenceStorage<S>* aStorage) 
            : mStorage(aStorage)
        {
            if (mStorage)
            {
                mStorage->addRef();
            }
        }

        bool operator == (const SmartPtr <T>& p)
        { 
            if (mStorage && p.mStorage)
            {
                return (mStorage == p.mStorage->getImpl());
            }

            if (mStorage && !p.mStorage)
            {
                return (mStorage == NULL);
            }

            if (!mStorage && p.mStorage)
            {
                return (p.mStorage == NULL);
            }

            return true;
        }

        bool operator == (const T* p)
        { 
            if ( !mStorage && !p ||
                 mStorage && !mStorage->getImpl() && !p ||
                 mStorage && p && mStorage->getImpl() == p )
            {
                return true;
            }

            return false;
        }

        bool operator != (const SmartPtr <T>& p) 
        { 
            return !(*this == p);
        }

        bool operator != (const T* p)
        { 
            return !(*this == p);
        }

        ~SmartPtr()
        {
            if(mStorage && mStorage->release() == 0 && mStorage->getWeakCount() == 0)
            {
                delete mStorage;
            }
        }

        T* operator & ()
        { 
            return mStorage ? mStorage->getImpl() : NULL;
        }

        T* operator -> ()
        { 
            return mStorage ? mStorage->getImpl() : NULL;
        }
    
        SmartPtr <T> & operator = (const SmartPtr <T> & p)
        {
            if (this != &p)
            {
                if (mStorage != p.mStorage)
                {
                    if (mStorage && mStorage->release() == 0 && mStorage->getWeakCount() == 0)
                    {
                        delete mStorage;
                    }
                }

                mStorage = p.mStorage;

                if (mStorage)
                {
                    mStorage->addRef();
                }
            }

            return *this;
        }

        void release()
        {
            if (mStorage && *mStorage)
            {
                mStorage->checkedDelete(*mStorage);

                mStorage->setImpl(NULL);
            }
        }
    
        template < typename D >
        SmartPtr<D> staticCast()
        {
            return SmartPtr<D>(mStorage->staticCast<D>());
        }
    };    

    template < typename T >
    class WeakPtr
    {
    private:
        ReferenceStorage<T>* mStorage;      

    public:

        WeakPtr()
            : mStorage(NULL)
        {}

        WeakPtr(const SmartPtr <T> & p)
            : mStorage(p.mStorage)
        {
            if (mStorage)
            {
                mStorage->addWeakRef();
            }
        }

        ~WeakPtr()
        {
            if(mStorage && mStorage->releaseWeak() == 0 && mStorage->getCount() == 0)
            {
                delete mStorage;
            }
        }

        SmartPtr <T> lock()
        {
            return SmartPtr <T>(mStorage);
        }
    };

} // namespace System

#endif // _SMARTPTR_H_