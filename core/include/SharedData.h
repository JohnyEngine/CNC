#ifndef __SHAREDDATA_H_
#define __SHAREDDATA_H_

#include <algorithm>

/**
 * \warning This class isn't thread-safe! In particular, we should use atomic
 * operations when incrementing or decrementing the reference count. See Boost's
 * shared_ptr for an alternative.
 */
template< typename T >
class SharedData
{
public:
    SharedData( T* data = 0 );
    SharedData( const SharedData<T>& sharedData );
    ~SharedData();

    void swap( SharedData<T>& sharedData );
    SharedData<T>& operator= ( SharedData<T> sharedData );

    T& operator[] ( int i ) const;

private:
    T* data_;
    int* refcount_;
};

template< typename T >
SharedData<T>::SharedData( T* data )
    : data_(data)
{
    try {
        refcount_ = new int(1);
    }
    catch (...) {
        delete[] data_;
        throw;
    }
}

template< typename T >
SharedData<T>::SharedData( const SharedData<T>& sharedData )
    : data_( sharedData.data_ )
    , refcount_( sharedData.refcount_ )
{
    ++*refcount_;
}

template< typename T >
SharedData<T>::~SharedData()
{
    if ( --*refcount_ == 0 ) {
        delete[] data_;
        delete refcount_;
    }
}

template< typename T >
void SharedData<T>::swap( SharedData<T>& sharedData )
{
    std::swap( sharedData.data_,     data_     );
    std::swap( sharedData.refcount_, refcount_ );
}

template< typename T >
SharedData<T>& SharedData<T>::operator= ( SharedData<T> sharedData )
{
    swap(sharedData);
    return *this;
}

template< typename T >
T& SharedData<T>::operator[] ( int i ) const
{
    assert(data_);
    return data_[i];
}

#endif // __SHAREDDATA_H_
