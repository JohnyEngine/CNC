#ifndef __GEOMETRY_H_
#define __GEOMETRY_H_

#include "Octree.h"

#define TREE_SIZE 4096

class Geometry : public Octree<float>
{
public:
	Geometry();

	~Geometry(){}

private:
};


#endif // __GEOMETRY_H_

