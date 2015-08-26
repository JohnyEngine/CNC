#include "Part.h"
#include "Geometry.h"


int main()
{
	Part part;

	part.setGeometry(GeometryPtr(new Geometry()));

	return 0;
}