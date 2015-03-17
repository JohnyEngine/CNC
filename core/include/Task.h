#ifndef _TASK_H_
#define _TASK_H_

#include <SmartPtr.h>
#include <Locker.h>

namespace System
{

    class Task: protected Locker
    {
        friend class TaskManager;

    public:

        class State
        {
        public:
            static const unsigned int None          = 0;
            static const unsigned int Started       = 1;
            static const unsigned int Stopped       = 2;
            static const unsigned int Canceled      = 3;
            static const unsigned int Error         = 4;
            typedef unsigned int Value;
        };

        class Type
        {
        public:
            static const unsigned int Serial        = 0;
            static const unsigned int Parallel      = 1;
            typedef unsigned int Value;
        };

        Task(Type::Value aType = Type::Serial);

        virtual ~Task ();

        void setType(Type::Value aType);

        Type::Value getType();

        virtual State::Value start() = 0;

        virtual void stop();

        State::Value getState();

    protected:

        void setId(unsigned int aId);

        unsigned int getId();

        void execute();

        void setState(State::Value aState);

        virtual void onChangeState(State::Value aPreviousState, State::Value aCurrentState);

    private:

        unsigned int mType;
        unsigned int mId;
        State::Value mState;
    }; 

    typedef SmartPtr<Task> TaskPtr;

} // namespace System

#endif // _TASK_H_
