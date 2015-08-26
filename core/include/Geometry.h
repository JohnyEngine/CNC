#ifndef __GEOMETRY_H_
#define __GEOMETRY_H_

#include "Global.h"
#include <vector>


struct Triangle {
	FVector3 p[3]; //!< Position of vertices.
	FVector3 n[3]; //!< Normal vectors.
	FVector3 c[3]; //!< Color vectors.

	/*!\brief Calculates normals for the corners of a triangle.
	*
	*  If no normals can be provided from elsewhere, this function
	*  can generate a set. The normal vectors n[0] to n[2] are all
	*  set normal to the plane of the triangle. Orientation is
	*  right handed.
	*/
	void CalculateNormal()
	{
		n[0].set((p[1] - p[0]) * (p[2] - p[1]));
		n[0].normalize();
		n[1].set(n[0]);
		n[2].set(n[0]);
	}

};

typedef System::SmartPtr<Triangle> TrianglePtr;

class Geometry
{
public:
	Geometry();

	~Geometry(){}

	void clear();

	//void add(Geometry* geometry){}

//protected:
	std::string name;
	FVector3 color;
	FVector3 colorNewObjects;
	void AddTriangle(const Triangle &tri, bool copyNormals = true);

	std::vector<TrianglePtr> triangles; //!< The storage of the geometric data.

private:
};

typedef System::SmartPtr<Geometry> GeometryPtr;


#endif // __GEOMETRY_H_

