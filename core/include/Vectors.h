#ifndef __VECTOR_H_
#define __VECTOR_H_

#include "NumTraits.h"

template< typename T, int N >
class Vector
{
public:
    Vector();
    Vector( const T& value );

    template< typename T2 >
    Vector( const Vector<T2,N>& v );

	void operator=(const Vector<T, N>& v)
	{
		for (int i = 0; i < N; ++i) {
			data_[i] = v.data_[i];
		}
	}

    template< typename T2 >
    Vector<T,N>& operator= ( const Vector<T2,N>& v );

    const T& at( int i ) const { return data_[i]; }
    const T& operator() ( int i ) const { return at(i); }
    T& operator() ( int i ) { return data_[i]; }

    const T* data() const { return data_; }
    T* data() { return data_; }

    void operator+= ( const Vector<T,N>& v )
    {
        for ( int i = 0; i < N; ++i ) {
            data_[i] += v.data_[i];
        }
    }

    void operator-= ( const Vector<T,N>& v )
    {
        for ( int i = 0; i < N; ++i ) {
            data_[i] -= v.data_[i];
        }
    }

    void operator*= ( const Vector<T,N>& v )
    {
        for ( int i = 0; i < N; ++i ) {
            data_[i] *= v.data_[i];
        }
    }

    void operator*= ( const T& x )
    {
        for ( int i = 0; i < N; ++i ) {
            data_[i] *= x;
        }
    }

    void operator/= ( const T& x )
    {
        for ( int i = 0; i < N; ++i ) {
            data_[i] /= x;
        }
    }

	//! Sets the vector to the given vector.
	void set(const Vector<T, N> &b) { *this = b; }


	//! Swap the vector with a given vector.
	void swap(Vector<T, N>& v)
	{
		float temp;

        for ( int i = 0; i < N; ++i ) {
			temp = v.data_[i];
			v.data_[i] = data_[i];
			data_[i] = temp;
        }
	}

	//! Normalizes the length of a vector.
	void normalize(void);

	//! Zeros a vector.
	void zero(void)
	{
		for (int i = 0; i < N; ++i) {
			data_[i] = 0;
		}
	}

private:
    T data_[N];
};

template< typename T, int N >
Vector<T,N>::Vector()
{
}

template< typename T, int N >
Vector<T,N>::Vector( const T& value )
{
    for ( int i = 0; i < N; ++i ) {
        data_[i] = value;
    }
}

template< typename T, int N >
template< typename T2 >
Vector<T,N>::Vector( const Vector<T2,N>& v )
{
    *this = v;
}

template< typename T, int N >
template< typename T2 >
Vector<T,N>& Vector<T,N>::operator= ( const Vector<T2,N>& v )
{
    for ( int i = 0; i < N; ++i ) {
        data_[i] = v(i);
    }
    return *this;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator+ (
        const Vector<T1,N>& v1, const Vector<T2,N>& v2 )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v3(v1);
    v3 += v2;
    return v3;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator- (
        const Vector<T1,N>& v1, const Vector<T2,N>& v2 )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v3(v1);
    v3 -= v2;
    return v3;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator* (
        const Vector<T1,N>& v1, const Vector<T2,N>& v2 )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v3(v1);
    v3 *= v2;
    return v3;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator* (
        const Vector<T1,N>& v1, const T2& x )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v2(v1);
    v2 *= x;
    return v2;
}

template< typename T, int N >
Vector<T,N> operator* ( const T& x, Vector<T,N> v1 )
{
    for ( int i = 0; i < N; ++i ) {
        v1(i) = x * v1(i);
    }
    return v1;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator* (
        const T2& x, const Vector<T1,N>& v1 )
{
    return x *
        Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N >(v1);
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator/ (
        const Vector<T1,N>& v1, const Vector<T2,N>& v2 )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v3(v1);
    v3 /= v2;
    return v3;
}

template< typename T1, typename T2, int N >
Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > operator/ (
        const Vector<T1,N>& v1, const T2& x )
{
    Vector< typename BinaryNumericTraits<T1,T2>::OpResult, N > v2(v1);
    v2 /= x;
    return v2;
}

template< typename T, int N >
T sum( const Vector<T,N>& v )
{
    T sum(0);
    for ( int i = 0; i < N; ++i ) {
        sum += v(i);
    }
    return sum;
}

template< typename T, int N >
T prod( const Vector<T,N>& v )
{
    T prod(1);
    for ( int i = 0; i < N; ++i ) {
        prod *= v(i);
    }
    return prod;
}

template< typename T, int N >
Vector<T,N> cumprod( const Vector<T,N>& v )
{
    Vector<T,N> p;
    T prev(1);
    for ( int i = 0; i < N; ++i ) {
        p(i) = prev = prev * v(i);
    }
    return p;
}

template< typename T, int N >
T norm( const Vector<T,N>& v )
{
    return sqrt( sum(v*v) );
}

template< typename T, int N >
void Vector<T, N>::normalize(void)
{
	T d = sum(*this);
	if (d > 0){
		(*this) /= d;
	}
}


#endif // __VECTOR_H_
