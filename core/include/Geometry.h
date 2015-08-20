#ifndef __GEOMETRY_H_
#define __GEOMETRY_H_

#include "Global.h"
#include "Octree.h"
#include <vector>


#define TREE_SIZE 4096

struct Triangle {
	FVector3 p[3]; //!< Position of vertices.
	FVector3 n[3]; //!< Normal vectors.
	FVector3 c[3]; //!< Color vectors.
};

class Geometry : public Octree<float>
{
public:
	Geometry();

	~Geometry(){}

	void clear(){}

	void add(Geometry* geometry){}

	std::size_t getCount(){ return 0; }

//protected:
	std::string name;
	FVector3 color;
	FVector3 colorNewObjects;
	void AddTriangle(const Triangle &tri, bool copyNormals = true){};

	std::vector<Triangle> triangles; //!< The storage of the geometric data.

private:
};

typedef System::SmartPtr<Geometry> GeometryPtr;


#endif // __GEOMETRY_H_

