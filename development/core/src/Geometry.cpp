#include "Geometry.h"

Geometry::Geometry()
{
}

void Geometry::clear()
{
	triangles.clear();
}

void Geometry::AddTriangle(const Triangle &tri, bool copyNormals)
{
	Triangle * temp = new Triangle(tri);
	if (!copyNormals) temp->CalculateNormal();
	triangles.push_back(temp);
}
