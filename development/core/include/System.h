#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#if (defined(DEBUG) || defined(_DEBUG))
# 	define ASSERTION(x) assert(x)
#else
# 	define ASSERTION(x) ((void)0)
#endif

namespace System
{
    typedef enum __RetValue__
    {
        noError = 0,
        waitTmeout,
        commonError
    } RetValue;

const unsigned int infinite = 0xFFFFFFFF;
} // namespace System

#endif // __SYSTEM_H__
