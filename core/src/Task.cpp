/**
*******************************************************************************

@file     Task.cpp

@brief    Набор классов представляющих реализацию выполняющихся задач.

@version  0.0.1

@author   Иван Андрущенко, (c) НКТ.

<b>Список изменений: </b>

@li 01/12/2008:  Создан.

******************************************************************************
*/

#include "Task.h"

namespace System
{

Task::Task(Task::Type::Value aType)
    : mType(aType)
    , mId(0)
    , mState(State::None)
{
}

Task::~Task()
{
}

void Task::setType(Task::Type::Value aType)
{
    mType = aType;
}

Task::Type::Value Task::getType(void)
{
    return mType;
}

void Task::setId(unsigned int aId)
{
    mId = aId;
}

unsigned int Task::getId(void)
{
    return mId;
}

void Task::stop()
{
    setState(State::Stopped);
}

Task::State::Value Task::getState()
{
    Locker::lock();

    State::Value state = mState;

    Locker::unlock();

    return state;
}

void Task::setState(Task::State::Value aState)
{
    Locker::lock();

    State::Value previousState = mState;

    if (mState != aState)
    {
        mState = aState;
    }

    Locker::unlock();

    onChangeState(previousState, aState);
}

void Task::onChangeState(State::Value aPreviousState, State::Value aCurrentState)
{
}

void Task::execute()
{
    setState(State::Started);

    setState(start());
}

} // namespace System
