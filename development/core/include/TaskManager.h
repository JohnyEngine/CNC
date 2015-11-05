#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include <Event.h>
#include <Task.h>
#include <map>

namespace System
{

    typedef std::map<unsigned int, TaskPtr> TaskList;

    class TaskManager: protected Event, public Task
    {
    public:

        static const unsigned int DEFAULT_TASK_TIMEOUT = 100;
        static const unsigned int DEFAULT_STOP_TIMEOUT = 5000;

        TaskManager();

        ~TaskManager(void);

        virtual State::Value start();

        virtual void stop();

        void add(TaskPtr aTask);

        void remove(unsigned int aId);

    protected:

        virtual void onChangeState(State::Value aPreviousState, State::Value aCurrentState);

#ifdef WIN32
        static unsigned __stdcall loop(void* lpParameter);
#else
        static void* loop(void* lpParameter);
#endif

    private:
        TaskList mTaskList;
        TaskList mFinishedTaskList;
#ifdef WIN32
        HANDLE mThreadHandle;
#else
        pthread_t mThreadHandle;
#endif
        unsigned int mThreadId;
        unsigned int mCounter;
    };

    typedef SmartPtr<TaskManager> TaskManagerPtr;

} // namespace System

#endif // _TASKMANAGER_H_
