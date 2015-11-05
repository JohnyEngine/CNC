
#include "TaskManager.h"
#include <process.h>

/*
******************************************************************************
*
* @brief Главный поток, запускающий и останавливающий задачи.
*
* @param  lpParameter  - указатель на TaskManager
*
* @return S_OK
*
******************************************************************************
*/

namespace System
{

#ifdef WIN32
unsigned __stdcall TaskManager::loop(void* lpParameter) {
#else
void* TaskManager::loop(void* lpParameter) {
#endif

    HRESULT hrRespone = S_FALSE;

    try
    {
        TaskManager* self = static_cast<TaskManager*>(lpParameter);

        if (self == NULL)
        {
            throw 1;
        }

        while (true)
        {
            /** Ожидаем события завершения задач. */
            if(self->wait(DEFAULT_TASK_TIMEOUT) != WAIT_TIMEOUT)
            {
                self->setState(Task::State::Canceled);

                break;
            }
            else
            {
                self->lock();

                TaskPtr task;
                unsigned int id = 0;

                TaskList::iterator it = self->mTaskList.begin();

                if (it != self->mTaskList.end())
                {
                    if (it->second != NULL)
                    {
                        id = it->first;

                        if (it->second->getType() == Task::Type::Parallel)
                        {
                            //Create child task manager to run parallel task

                            TaskManager* taskManager = new TaskManager();

                            it->second->setType(Task::Type::Serial);

                            taskManager->add(it->second);

                            task = TaskPtr(taskManager);
                        }
                        else if (it->second->getType() == Task::Type::Serial)
                        {
                            task = it->second;
                        }
                        
                        self->mTaskList.erase(it);
                    }
                }

                if (task != NULL)
                {
                    self->mFinishedTaskList.insert(std::make_pair(id, task));
                }

                self->unlock();

                if (task != NULL)
                {
                    task->execute();
                }
            }
        }

        hrRespone = S_OK;
    }
    catch(std::exception& e)
    {
        TaskManager* self = static_cast<TaskManager*>(lpParameter);

        if (self != NULL)
        {
            self->setState(Task::State::Error);
        }

        //todo: error to log
    }
    catch(...)
    {
        TaskManager* self = static_cast<TaskManager*>(lpParameter);

        if (self != NULL)
        {
            self->setState(Task::State::Error);
        }

        //todo: unknown error to log
    }

#ifdef WIN32
    _endthreadex(0);
#else
    pthread_exit(0);
#endif
    return hrRespone;
} /*ThreadTasks*/

#if __ANDROID__
//http://igourd.blogspot.com/2009/05/work-around-on-pthreadcancel-for.html
void thread_exit_handler(int sig)
{
    //printf("this signal is %d \n", sig);
    pthread_exit(0);
}

void setup_thread_exit_handler()
{
    static bool _inited = false;
    if (_inited)
        return;

    _inited = true;

    struct sigaction actions;
    memset(&actions, 0, sizeof(actions));
    sigemptyset(&actions.sa_mask);
    actions.sa_flags = 0;
    actions.sa_handler = thread_exit_handler;
    int rc = sigaction(SIGUSR1,&actions,NULL);
}

#endif

TaskManager::TaskManager()
    : Task()
    , mThreadHandle(INVALID_HANDLE_VALUE)
    , mThreadId(0)
    , mCounter(0)
{
}

TaskManager::~TaskManager()
{
    if (getState() == Task::State::Started)
    {
        stop();
    }
}

Task::State::Value TaskManager::start()
{
#ifdef WIN32
    mThreadHandle = (HANDLE)_beginthreadex(
        NULL, // no security
        65535,
        loop,
        this,
        0, // running
        &mThreadId
        );

    if (INVALID_HANDLE_VALUE == mThreadHandle)
    {
        return Task::State::Error;
    }
#else

    int failed = pthread_create(&mThreadHandle, NULL, &task, this);

    ASSERTION(!failed);

    mThreadId = mThreadHandle;
#endif

#if __ANDROID__
    setup_thread_exit_handler();
#endif
    
    if (!mThreadHandle)
    {
        return Task::State::Error;
    }

    return Task::State::Started;
}

void TaskManager::stop()
{
    if (mThreadHandle != NULL && mThreadHandle != INVALID_HANDLE_VALUE)
    {
        Event::signal();
        
#ifdef WIN32
        if (WaitForSingleObject(mThreadHandle, DEFAULT_STOP_TIMEOUT) != WAIT_OBJECT_0)     
        {
            // todo: error message to log && exit from application
            TerminateThread(mThreadHandle, 0);
        }

        CloseHandle(mThreadHandle);
#else
        int status = pthread_join(mThreadHandle, NULL);

#ifdef __ANDROID__
        if (status != 0 && )
        {
            status = pthread_kill(mThreadHandle,  );
        }
#endif
        if (status != 0)
        {
            // todo: error message to log && exit from application
        }
#endif        

        Task::stop();
    }
}

void TaskManager::add(TaskPtr aTask)
{
    if (aTask != NULL)
    {
        Locker::lock();

        aTask->setId(mCounter++);

        mTaskList.insert(std::make_pair(aTask->getId(), aTask));

        Locker::unlock();
    }
}

void TaskManager::remove(unsigned int aId)
{
    Locker::lock();

    TaskPtr task;

    TaskList::iterator it = mTaskList.find(aId);

    if (it != mTaskList.end())
    {
        task = it->second;

        mTaskList.erase(it);
    }

    Locker::unlock();

    if (task != NULL)
    {
        task->setState(Task::State::Canceled);
    }
}

void TaskManager::onChangeState(State::Value aPreviousState, State::Value aCurrentState)
{
    if (aCurrentState == Task::State::Canceled || aCurrentState == Task::State::Error)
    {
        Locker::lock();

        /** Прерываем задачи. */
        for (TaskList::iterator it = mTaskList.begin(); it != mTaskList.end(); it = mTaskList.erase(it))
        {
            if (it->second != NULL)
            {
                it->second->setState(aCurrentState);
            }
        }

        for (TaskList::iterator it = mFinishedTaskList.begin(); it != mFinishedTaskList.end(); it = mFinishedTaskList.erase(it))
        {
            if (it->second != NULL)
            {
                if (it->second->getState() == Task::State::Started)
                {
                    it->second->setState(Task::State::Stopped);

                    it->second->stop();
                }
            }
        }

        Locker::unlock();
    }
    else if (aCurrentState == Task::State::Stopped)
    {
        Locker::lock();

        /** Прерываем задачи. */
        for (TaskList::iterator it = mTaskList.begin(); it != mTaskList.end(); it = mTaskList.erase(it))
        {
            if (it->second != NULL)
            {
                it->second->setState(Task::State::Canceled);
            }
        }

        for (TaskList::iterator it = mFinishedTaskList.begin(); it != mFinishedTaskList.end(); it = mFinishedTaskList.erase(it))
        {
            if (it->second != NULL)
            {
                if (it->second->getState() == Task::State::Started)
                {
                    it->second->setState(aCurrentState);

                    it->second->stop();
                }
            }
        }

        Locker::unlock();
    }
}

} // namespace System
