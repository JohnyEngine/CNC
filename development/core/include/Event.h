#ifndef __EVENT_H_
#define __EVENT_H_ 

#ifdef WIN32
#include <windows.h>
#elif __APPLE__
#include <pthread.h>
#include <semaphore.h>
#include <Carbon/Carbon.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

#include "NonCopyable.h"

#include <assert.h>

#include <System.h>

namespace System
{

    class Event : NonCopyable
    {
    public:

	    Event();

	    ~Event();

	    RetValue wait(unsigned int timeout = infinite);

        bool signal();

    private:

    #ifdef WIN32
	    HANDLE m_syncObj;
    #elif __APPLE__
	    MPSemaphoreID m_syncObj;
    #else
	    sem_t m_syncObj;
    #endif

    };

} // namespace System

#endif /*__EVENT_H_*/
