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