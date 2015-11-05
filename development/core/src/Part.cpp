#include "Part.h"
#include "Geometry.h"

Part::Part()
 : mPosition(FVector3())
 , mScale(FVector3())
 , mRotation(FVector3())
 , mColor(FVector3())
{

}

void Part::setGeometry(const GeometryPtr& geometry)
{
	mGeometry = geometry;
}

Geometry& Part::getGeometry()
{
	return *&mGeometry;
}

void Part::setPosition(const FVector3& position)
{
	mPosition.set(position);
}

FVector3 Part::getPosition()
{
	return mPosition;
}

void Part::setScale(const FVector3& scale)
{
	mScale.set(scale);
}

FVector3 Part::getScale()
{
	return mScale;
}

void Part::setRotation(const FVector3& rotation)
{
	mRotation.set(rotation);
}

FVector3 Part::getRotation()
{
	return mRotation;
}

void Part::setColor(const FVector3& color)
{
	mColor.set(color);
}

FVector3 Part::getColor()
{
	return mColor;
}
