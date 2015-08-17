#ifndef __PART_H_
#define __PART_H_

#include "Global.h"

class Geometry;
typedef System::SmartPtr < Geometry > GeometryPtr;

class Part {
public:
	Part();
    ~Part(){}

	void setGeometry(const GeometryPtr& geometry);
	Geometry& getGeometry();

	void setPosition(const FVector3& position);
	FVector3 getPosition();

	void setScale(const FVector3& scale);
	FVector3 getScale();

	void setRotation(const FVector3& rotation);
	FVector3 getRotation();

	void setColor(const FVector3& color);
	FVector3 getColor();

private:
	GeometryPtr mGeometry;
	FVector3 mPosition;
	FVector3 mScale;
	FVector3 mRotation;
	FVector3 mColor;
}; 

#endif // __PART_H_