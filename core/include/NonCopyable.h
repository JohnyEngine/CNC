/*
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
*/
#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace System
{

    class NonCopyable
    {
        protected:
            NonCopyable() {}
            ~NonCopyable() {}

        private:

            NonCopyable( const NonCopyable& );
            const NonCopyable& operator=( const NonCopyable& );
    };

} // namespace System

#endif//_NONCOPYABLE_H_
