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
	mPosition.Set(position.x, position.y, position.z);
}

FVector3 Part::getPosition()
{
	return mPosition;
}

void Part::setScale(const FVector3& scale)
{
	mScale.Set(scale.x, scale.y, scale.z);
}

FVector3 Part::getScale()
{
	return mScale;
}

void Part::setRotation(const FVector3& rotation)
{
	mRotation.Set(rotation.x, rotation.y, rotation.z);
}

FVector3 Part::getRotation()
{
	return mRotation;
}

void Part::setColor(const FVector3& color)
{
	mColor.Set(color.x, color.y, color.z);
}

FVector3 Part::getColor()
{
	return mColor;
}
