#include "Part.h"
#include "Geometry.h"


int main()
{
	Part part;

	GeometryPtr geometry = GeometryPtr(new Geometry());

	part.setGeometry(geometry);

	part.getGeometry()(1, 2, 3) = 3.1416f;      /* Put pi in (1,2,3). */
	part.getGeometry().erase(1, 2, 3);					/* Erase that node. */


	return 0;
}