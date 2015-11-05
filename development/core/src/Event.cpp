#include "Event.h"

#ifdef WIN32
#include <process.h>
#else
#ifndef __APPLE__
#include <time.h>
#endif
#endif

#include <limits>
#include <System.h>

namespace System
{

    Event::Event()
    {
#ifdef WIN32
        m_syncObj = CreateSemaphore(
            0,    // Security attributes
            0,    // Initial count zero (everybody will wait)
            std::numeric_limits<int>::max(), // the mamimum number of resources
            0    // No name for this semaphore
            );
#elif __APPLE__

        OSStatus result = MPCreateSemaphore(std::numeric_limits<int>::max(), 0, &m_syncObj);

        ASSERTION(result == 0);

#else
        int result = sem_init(&m_syncObj, 0, 0);

        ASSERTION(result != -1);
#endif
    }

    Event::~Event()
    {
#ifdef WIN32
        CloseHandle(m_syncObj);
#elif __APPLE__
        OSStatus result = MPDeleteSemaphore(m_syncObj);

        ASSERTION(result == 0);
#else
        int result = sem_destroy(&m_syncObj);
        ASSERTION(result != -1);
#endif
    }

    RetValue Event::wait(unsigned int timeout)
    {
        RetValue ret = noError;

#ifdef WIN32
        switch (WaitForSingleObject(m_syncObj, timeout == infinite ? INFINITE : timeout))
        {
        case WAIT_TIMEOUT:
            if (timeout != INFINITE)
            {
                ret = commonError;
            }
            else
            {
                ret = waitTmeout;
            }
            break;

        case WAIT_OBJECT_0:
            break;

        default:
            ret = commonError;
            break;
        }
#elif __APPLE__
        OSStatus result = MPWaitOnSemaphore (m_syncObj, timeout == infinite ? kDurationForever : timeout);

        ASSERTION(result == 0);
#else
        int result = 0;

        if (timeout == infinite)
        {
            result = sem_wait(&m_syncObj);
        }
        else
        {
            timespec _time(0, timeout * 1000000); 
            result = sem_timedwait(&m_syncObj, &_time);
        }

        ASSERTION(result != -1);
#endif

        return ret;
    }

    bool Event::signal()
    {
#ifdef WIN32
        if (!ReleaseSemaphore(m_syncObj, 1, 0))
            return false;
#elif __APPLE__
        OSStatus result = MPSignalSemaphore (m_syncObj);
        GK_ASSERT(result == 0);
#else
        int result = sem_post(&m_syncObj);
        GK_ASSERT(result != -1);
#endif
        return true;
    }

} // namespace System
