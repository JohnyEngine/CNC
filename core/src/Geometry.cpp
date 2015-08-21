#include "Geometry.h"

Geometry::Geometry()
	: Octree(TREE_SIZE)
{
}

void Geometry::AddTriangle(const Triangle &tri, bool copyNormals)
{
	Triangle * temp = new Triangle(tri);
	if (!copyNormals) temp->CalculateNormal();
	triangles.push_back(temp);
}
