#include "Vector3.h"

template< typename T >
void Vector3<T>::Zero(void)
{
	x = y = z = 0.0;
}

template< typename T >
void Vector3<T>::Swap(Vector3<T>& b)
{
	float temp;
	temp = b.x;
	b.x = this->x;
	this->x = temp;

	temp = b.y;
	b.y = this->y;
	this->y = temp;

	temp = b.z;
	b.z = this->z;
	this->z = temp;
}

template< typename T >
Vector3<T> Vector3<T>::Normalize(void)
{
	T d = Abs();
	if (d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
	return Vector3<T>(x, y, z);
}