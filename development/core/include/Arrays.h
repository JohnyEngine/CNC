#ifndef __ARRAYS_H_
#define __ARRAYS_H_

#include "SharedData.h"
#include "Vectors.h"

template< typename T, int N >
class Array
{
public:
    Array();
    Array( const Vector<int,N>& sizes );

    const Vector<int,N>& sizes() const;

    const T& at( const Vector<int,N>& indices ) const;
    const T& operator() ( const Vector<int,N>& indices ) const;
    T& operator() ( const Vector<int,N>& indices );

    Array<T,N> subarray( const Vector<int,N>& begin,
                         const Vector<int,N>& end );

private:
    int dataIndex( const Vector<int,N>& indices ) const;

private:
    SharedData<T> data_;
    int offset_;
    Vector<int,N> strides_;
    Vector<int,N> sizes_;
};

template< typename T, int N >
Array<T,N>::Array()
    : data_(0)
    , sizes_(0)
{
}

template< typename T, int N >
Array<T,N>::Array( const Vector<int,N>& sizes )
    : data_( new T[prod(sizes)] )
    , offset_(0)
    , strides_( cumprod(sizes)/sizes(0) )
    , sizes_(sizes)
{
}

template< typename T, int N >
const Vector<int,N>& Array<T,N>::sizes() const
{
    return sizes_;
}

template< typename T, int N >
const T& Array<T,N>::at( const Vector<int,N>& indices ) const
{
    return data_[ dataIndex(indices) ];
}

template< typename T, int N >
const T& Array<T,N>::operator() ( const Vector<int,N>& indices ) const
{
    return at(indices);
}

template< typename T, int N >
T& Array<T,N>::operator() ( const Vector<int,N>& indices )
{
    return data_[ dataIndex(indices) ];
}

template< typename T, int N >
int Array<T,N>::dataIndex( const Vector<int,N>& indices ) const
{
    for ( int i = 0; i < N; ++i ) {
        assert( indices(i) >= 0 && indices(i) < sizes_(i) );
    }

    return offset_ + sum( indices * strides_ );
}

template< typename T, int N >
Array<T,N> Array<T,N>::subarray( const Vector<int,N>& begin,
                                 const Vector<int,N>& end )
{
    Array<T,N> sub;
    sub.data_ = data_;
    sub.offset_ = dataIndex(begin);
    sub.strides_ = strides_;
    sub.sizes_ = end - begin;
    return sub;
}

template< typename T >
class Array2D : public Array<T, 2>
{
public:
	Array2D();
	Array2D(int m, int n);
	Array2D(const Array<T, 2>& array);

	int M() const;
	int N() const;

	const T& at(int i, int j) const;
	const T& operator() (int i, int j) const;
	T& operator() (int i, int j);

	Array2D<T> subarray(int iBegin, int jBegin, int iEnd, int jEnd);
};

template< typename T >
Array2D<T>::Array2D()
	: Array<T, 2>()
{
}

template< typename T >
Array2D<T>::Array2D(int m, int n)
	: Array<T, 2>()
{
	Vector<int, 2> sizes;
	sizes(1) = m;
	sizes(0) = n;

	Array<T, 2>::operator= (Array<T, 2>(sizes));
}

template< typename T >
Array2D<T>::Array2D(const Array<T, 2>& array)
	: Array<T, 2>(array)
{
}

template< typename T >
int Array2D<T>::M() const
{
	return this->sizes()(1);
}

template< typename T >
int Array2D<T>::N() const
{
	return this->sizes()(0);
}

template< typename T >
const T& Array2D<T>::at(int i, int j) const
{
	Vector<int, 2> indices;
	indices(1) = i;
	indices(0) = j;
	return Array<T, 2>::at(indices);
}

template< typename T >
const T& Array2D<T>::operator() (int i, int j) const
{
	return at(i, j);
}

template< typename T >
T& Array2D<T>::operator() (int i, int j)
{
	Vector<int, 2> indices;
	indices(1) = i;
	indices(0) = j;
	return Array<T, 2>::operator()(indices);
}

template< typename T >
Array2D<T> Array2D<T>::subarray(int iBegin, int jBegin, int iEnd, int jEnd)
{
	Vector<int, 2> begin, end;
	begin(1) = iBegin;
	begin(0) = jBegin;
	end(1) = iEnd;
	end(0) = jEnd;
	return Array<T, 2>::subarray(begin, end);
}

#endif  // __ARRAYS_H_
