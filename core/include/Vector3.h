/*!\class Vector3
 * \brief Contains a vector in 3D space
 */

#ifndef __VECTOR3_H_
#define __VECTOR3_H_

#include <math.h>
#include "Vectors.h"

template< typename T >
class Vector3 : public Vector<T, 3> {
	// Constructor/Destructor:
public:
	Vector3(T px = 0.0, T py = 0.0, T pz = 0.0)
		: x((*this)(0))
		, y((*this)(1))
		, z((*this)(2))
	{
		x = px;
		y = py;
		z = pz;
	}

	~Vector3(void){}

	// Member variables:
public:
	T& x;
	T& y;
	T& z;

	// Methods:
public:

	//! Overloaded operator for vector addition.
	const Vector3<T> operator+(const Vector3<T>& a) const
	{
		Vector3<T> temp = *this;
		temp += a;
		return temp;
	}

	//! Overloaded operator for vector subtraction.
	const Vector3<T> operator-(const Vector3<T>& a) const
	{
		Vector3<T> temp = *this;
		temp -= a;
		return temp;
	}


	//! Overloaded operator for vector negation.
	const Vector3<T> operator-() const
	{
		Vector3<T> temp(-this->x, -this->y, -this->z);
		return temp;
	}

	const Vector3<T> operator*(const Vector3& b) const
	{
		Vector3<T> temp = *this;
		temp *= b;
		return temp;
	}


	//! Overloaded operator for scalar product.
	const Vector3<T> operator*(const T &b) const
	{
		Vector3 temp = *this;
		temp *= b;
		return temp;
	}

	//! Overloaded operator for scalar division.
	const Vector3 operator/(const float &b) const
	{
		Vector3 temp = *this;
		temp /= b;
		return temp;
	}

	//! Comparison operator.
	bool operator==(const Vector3<T> &b) const
	{
		T epsilon = 1e-5;
		T epsilon2 = epsilon * epsilon;
		return (((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y
				- b.y) + (this->z - b.z) * (this->z - b.z)) <= epsilon2);
	}


	//! Comparison operator.
	bool operator!=(const Vector3<T> &b) const
	{
		return !(*this == b);
	}


	//! Zeros a vector.
	void Zero(void);

	//! Sets the vector to the given coordinates.
	void Set(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	//! Sets the vector to the given vector.
	void Set(const Vector3<T> &b)
	{
		this->x = b.x;
		this->y = b.y;
		this->z = b.z;
	}


	//! Swap the vector with a given vector.
	void Swap(Vector3<T>& b);


	//! Normalizes the length of a vector.
	Vector3<T> Normalize(void);
};

typedef Vector3<float> FVector3;

#endif // __VECTOR3_H_
