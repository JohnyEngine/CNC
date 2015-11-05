#ifndef __LOCKER_H_
#define __LOCKER_H_

#include "NonCopyable.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

namespace System
{

    class Locker : NonCopyable
    {
    public:

        Locker();

        ~Locker();

        class Lock
        {
        public:
            Lock(Locker& obj);
            ~Lock();

        private:
            Locker& m_obj;
        };

        void lock();

        void unlock();

    private:

#ifdef WIN32
        CRITICAL_SECTION m_cs;
#else
        pthread_mutex_t m_cs;
#endif
    };

} // namespace System

#endif /*__LOCKER_H_*/
