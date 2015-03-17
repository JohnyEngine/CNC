#include "Locker.h"
#include "System.h"

#ifdef WIN32
#include <process.h>
#endif

namespace System
{

Locker::Locker()
{
#ifdef WIN32
    InitializeCriticalSection(&m_cs);
#else
    int failed = pthread_mutex_init(&m_cs, NULL);
    ASSERTION(!failed);
#endif
}

Locker::~Locker()
{
#ifdef WIN32
    DeleteCriticalSection(&m_cs);
#else
    int failed = pthread_mutex_destroy(&m_cs);
    ASSERTION(!failed);
#endif
}

void Locker::lock()
{
#ifdef WIN32
    EnterCriticalSection(&m_cs);
#else
    int failed = pthread_mutex_lock(&m_cs);
    ASSERTION(!failed);
#endif

}

void Locker::unlock()
{
#ifdef WIN32
    LeaveCriticalSection(&m_cs);
#else
    int failed = pthread_mutex_unlock(&m_cs);
    ASSERTION(!failed);
#endif
}

Locker::Lock::Lock(Locker& obj)
    : m_obj(obj)
{
    m_obj.lock();
}

Locker::Lock::~Lock()
{
    m_obj.unlock();
}

} // namespace System
