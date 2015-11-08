// Extrude 3D model (e3d) Copyright ©2011 Adrian Kennard
// STL processing functions
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details. 
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <stdio.h>
#include <string.h>
#include "err.h"
#include <ctype.h>

#include "e3d-stl.h"

void panic(const char *e, int lineno, const char *line)
{
	errx(1, "Line %d: %s\n%s\n", lineno, e, line);
}

int
strncasecmp(
	const char *s1,
	const char *s2,
	size_t n)
{
	if (n == 0)
		return 0;

	while (n-- != 0 && tolower(*s1) == tolower(*s2))
	{
		if (n == 0 || *s1 == '\0' || *s2 == '\0')
			break;
		s1++;
		s2++;
	}

	return tolower(*(unsigned char *)s1) - tolower(*(unsigned char *)s2);
}

stl_t *
stl_read (const char *filename)
{				// Read an STL file
  FILE *f = fopen (filename, "r");
  if (!f)
    return NULL;
  stl_t *stl = mymalloc (sizeof (*stl));
  stl->filename = strdup (filename);
  facet_t *element = NULL, **next = &stl->facets;
  int vertex = 0, lineno = 0;
  char line[100];
  while (fgets (line, sizeof (line), f))
    {
      lineno++;
      char *p = line + strlen (line);
      while (p > line && p[-1] < ' ')
	p--;
      *p = 0;
      for (p = line; isspace (*p); p++);
      if (!strncasecmp (p, "solid", 5))
	{
	  if (stl->name)
	    panic ("More than one solid in STL", lineno, line);
	  p += 5;
	  while (isspace (*p))
	    p++;
	  stl->name = strdup (p);
	  continue;
	}
      if (!strncasecmp (p, "facet", 5))
	{
	  if (element)
	    panic ("facet unexpected", lineno, line);
	  continue;
	}
      if (!strncasecmp (p, "outer", 5))
	{
	  if (element)
	    panic ("outer unexpected", lineno, line);
	  vertex = 0;
	  element = mymalloc (sizeof (*element));
	  *next = element;
	  next = &element->next;
	  continue;
	}
      if (!strncasecmp (p, "endloop", 7))
	{
	  if (vertex != 3)
	    panic ("Unexpected endloop (not 3 vertices)", lineno, line);
	  vertex = 0;
	  continue;
	}
      if (!strncasecmp (p, "endfacet", 8))
	{
	  if (vertex || !element)
	    panic ("Unexpected endfacet", lineno, line);
	  element = NULL;
	  stl->count++;
	  continue;
	}
      if (!strncasecmp (p, "vertex", 6))
	{
	  if (vertex >= 3)
	    panic ("Too many vertices", lineno, line);
	  long double x, y, z;
	  if (sscanf (p, "vertex %Lf %Lf %Lf", &x, &y, &z) != 3)
	    panic ("Cannot parse vertex", lineno, line);
#ifdef	FIXED
	  element->vertex[vertex].x = x * fixed;
	  element->vertex[vertex].y = y * fixed;
	  element->vertex[vertex].z = z * fixed;
#else
	  element->vertex[vertex].x = x;
	  element->vertex[vertex].y = y;
	  element->vertex[vertex].z = z;
#endif
	  if ((!stl->count && !vertex) || element->vertex[vertex].x < stl->min.x)
	    stl->min.x = element->vertex[vertex].x;
	  if ((!stl->count && !vertex) || element->vertex[vertex].x > stl->max.x)
	    stl->max.x = element->vertex[vertex].x;
	  if ((!stl->count && !vertex) || element->vertex[vertex].y < stl->min.y)
	    stl->min.y = element->vertex[vertex].y;
	  if ((!stl->count && !vertex) || element->vertex[vertex].y > stl->max.y)
	    stl->max.y = element->vertex[vertex].y;
	  if ((!stl->count && !vertex) || element->vertex[vertex].z < stl->min.z)
	    stl->min.z = element->vertex[vertex].z;
	  if ((!stl->count && !vertex) || element->vertex[vertex].z > stl->max.z)
	    stl->max.z = element->vertex[vertex].z;
	  vertex++;
	  continue;
	}
      if (!strncasecmp (p, "endsolid", 8))
	{
	  if (element)
	    panic ("Unexpected endsolid", lineno, line);
	  break;
	}
      panic ("unexpected line", lineno, line);
    }
  fclose (f);
  if (debug)
    {
      fprintf (stderr, "STL read %d facets from %s [%s]\n", stl->count, stl->filename, stl->name);
      fprintf (stderr, "Min X %s\n", dimout (stl->min.x));
      fprintf (stderr, "Max X %s\n", dimout (stl->max.x));
      fprintf (stderr, "Min Y %s\n", dimout (stl->min.y));
      fprintf (stderr, "Max Y %s\n", dimout (stl->max.y));
      fprintf (stderr, "Min Z %s\n", dimout (stl->min.z));
      fprintf (stderr, "Max Z %s\n", dimout (stl->max.z));
    }
  return stl;
}

void
stl_origin (stl_t * stl)
{				// Set file at zero x/y/z
  facet_t *e;
  for (e = stl->facets; e; e = e->next)
    {
      int v;
      for (v = 0; v < 3; v++)
	{
	  e->vertex[v].x -= stl->min.x;
	  e->vertex[v].y -= stl->min.y;
	  e->vertex[v].z -= stl->min.z;
	}
    }
  stl->max.x -= stl->min.x;
  stl->max.y -= stl->min.y;
  stl->max.z -= stl->min.z;
  stl->min.x = 0;
  stl->min.y = 0;
  stl->min.z = 0;
  if (debug)
    {
      fprintf (stderr, "Origin adjusted\n");
      fprintf (stderr, "Max X %s\n", dimout (stl->max.x));
      fprintf (stderr, "Max Y %s\n", dimout (stl->max.y));
      fprintf (stderr, "Max Z %s\n", dimout (stl->max.z));
    }
}
