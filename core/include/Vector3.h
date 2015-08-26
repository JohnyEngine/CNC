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

};

typedef Vector3<float> FVector3;

#endif // __VECTOR3_H_
