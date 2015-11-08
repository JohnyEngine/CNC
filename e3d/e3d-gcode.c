// Extrude 3D model (e3d) Copyright ©2011 Adrian Kennard
// Output GCODE
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

#include "e3d-gcode.h"

typedef struct _params_
{
	int			*mirror;
	poly_dim_t	*cx;
	poly_dim_t  *zspeed;
	FILE		*o;
	int			*eplaces;
	long long	*t;
	poly_dim_t  *px;
	poly_dim_t  *py;
	long double *pe;
	poly_dim_t	*layer;
	double		*fillflow;
	double		*back;
	poly_dim_t  *hop;
	poly_dim_t	*z;
} params, *pparams;


void g1(poly_dim_t x, poly_dim_t y, poly_dim_t z, long double e, poly_dim_t f, pparams params)
{
	static long double le = 0;
	static poly_dim_t lx = 0, ly = 0, lz = 0, lf = 0;
	if (*params->mirror)
		x = (*params->cx) * 2 - x;
	if (x == lx && y == ly && z == lz && e == le && f == lf)
		return;
	if (z != lz && *params->zspeed)
	{				// check max speed
		poly_dim_t d = sqrtl((x - lx) * (x - lx) + (y - ly) * (y - ly) + (z - lz) * (z - lz) + (d2dim(e) - d2dim(le)) * (d2dim(e) - d2dim(le)));
		poly_dim_t dz = lz - z;
		if (dz < 0)
			dz = 0 - dz;
		if (d * (*params->zspeed) < dz * f)
			f = d * (*params->zspeed) / dz;
	}
	fprintf(params->o, "G1");
	if (x != lx)
		fprintf(params->o, " X%s", dimout(x));
	if (y != ly)
		fprintf(params->o, " Y%s", dimout(y));
	if (z != lz)
		fprintf(params->o, " Z%s", dimout(z));
	if (e != le)
		fprintf(params->o, " E%.*Lf", *params->eplaces, e);
	if (f != lf)
		fprintf(params->o, " F%s", dimout(f * 60));	// feeds are per minute
	poly_dim_t d = sqrtl((x - lx) * (x - lx) + (y - ly) * (y - ly) + (z - lz) * (z - lz) + (d2dim(e) - d2dim(le)) * (d2dim(e) - d2dim(le)));
	if (d && f)
		(*params->t) += d * 1000000LL / f;
	lx = x;
	ly = y;
	lz = z;
	le = e;
	lf = f;
	fprintf(params->o, "\n");
}

void move(poly_dim_t x, poly_dim_t y, poly_dim_t z, double back, poly_dim_t speed, pparams params)
{
	g1((*params->px) = x, (*params->py) = y, z, (*params->pe) - back, speed, params);
}
void extrude(poly_dim_t x, poly_dim_t y, poly_dim_t z, poly_dim_t speed, double flowrate, pparams params)
{
	poly_dim_t d = sqrtl((x - (*params->px)) * (x - (*params->px)) + (y - (*params->py)) * (y - (*params->py)));
	g1((*params->px) = x, (*params->py) = y, z, (*params->pe) = (*params->pe) + (dim2d(d) * flowrate), speed, params);
}
void plot_loops(polygon_t * p, poly_dim_t speed, double flowrate, int dir, params* params)
{
	if (!p)
		return;
	poly_contour_t *c;
	for (c = p->contours; c; c = c->next)
		if (c->vertices && (!dir || dir == c->dir))
		{
			poly_vertex_t *v = c->vertices;
			poly_dim_t d = sqrtl(((*params->px) - v->x) * ((*params->px) - v->x) + ((*params->py) - v->y) * ((*params->py) - v->y));
			if ((*params->pe) && d > (*params->layer) * 5)
			{			// hop and pull back extruder while moving
				move(*params->px, *params->py, *params->z + *params->hop, *params->back, speed, params);
				move(v->x, v->y, *params->z + *params->hop, *params->back, speed, params);
			}
			if (d)
				move(v->x, v->y, *params->z, 0, speed, params);
			double flow = (c->vertices->flag ? *params->fillflow : 1);
			for (v = c->vertices->next; v; v = v->next)
			{
				extrude(v->x, v->y, *params->z, speed, flowrate * flow, params);
				flow = (v->flag ? *params->fillflow : 1);
			}
			if (c->dir)
			{
				v = c->vertices;
				extrude(v->x, v->y, *params->z, speed, flowrate * flow, params);
			}
		}
}

unsigned int
gcode_out (const char *filename, stl_t * stl, double flowrate, poly_dim_t layer, poly_dim_t speed0, poly_dim_t speed, poly_dim_t zspeed, double back,
	   poly_dim_t hop, int mirror, double anchorflow, double fillflow, int eplaces, int tempbed, int temp0, int temp, int quiet)
{				// returns time estimate in seconds
  FILE *o = fopen (filename, "w");
  if (!o)
    err (1, "Cannot open %s for SVG", filename);
  poly_dim_t cx = (stl->min.x + stl->max.x) / 2;
  poly_dim_t cy = (stl->min.y + stl->max.y) / 2;

  // pre
  fprintf (o,			//
	   "G21             ; metric\n"	//
	   "G90             ; absolute\n"	//
	   "G92 Z0 E0       ; reset Z and E \n"	//
	   "M106            ; fan on\n"	//
	   "G1 Z2 F60	    ; up\n"	//  avoid issues with end stop
	   "G1 Z0.1	    ; down\n"	//
	   "G92 Z0	    ; origin\n"	//
    );
  fprintf (o, "G92");		// origin starts assuming in middle of print
  fprintf (o, " X%s", dimout (cx));
  fprintf (o, " Y%s", dimout (cy));
  fprintf (o, "\n");
  if (tempbed)
    fprintf (o, "M140 S%d\n", tempbed);
  if (temp0)
    fprintf (o, "M109 S%d\n", temp0);
  else if (temp)
    fprintf (o, "M109 S%d\n", temp);
  long long t = 0;

  //g1

  poly_dim_t px = 0, py = 0;
  long double pe = 0;

  //move
  //extrude
  poly_dim_t z = 0;
  //plot_loops

  // layers
  slice_t *s;
  s = stl->slices;
  
  params p;

  p.mirror	= &mirror;
  p.cx		= &cx;
  p.zspeed	= &zspeed;
  p.o		= o;
  p.eplaces = &eplaces;
  p.t		= &t;
  p.px		= &px;
  p.py		= &py;
  p.pe		= &pe;
  p.layer	= &layer;
  p.fillflow = &fillflow;
  p.back	= &back;
  p.hop		= &hop;
  p.z		= &z;

  plot_loops (stl->border, speed, stl->anchor ? 0 : flowrate, 1, &p);	// Ensures end-stops hit if no space, and if no anchor then ensures extrusion working
  plot_loops (stl->anchor, speed0, flowrate, 1, &p);
  plot_loops (stl->anchor, speed0, flowrate, -1, &p);
  plot_loops (stl->anchorjoin, speed0, flowrate * anchorflow, 1, &p);
  plot_loops (stl->anchorjoin, speed0, flowrate * anchorflow, -1, &p);
  poly_dim_t sp = speed0;
  while (s)
   {
      int e;
      plot_loops (s->extrude[EXTRUDE_PERIMETER], sp, flowrate, 1, &p);
      plot_loops (s->extrude[EXTRUDE_PERIMETER], sp, flowrate, -1, &p);
      for (e = EXTRUDE_PERIMETER + 1; e < EXTRUDE_PATHS - 1; e++)
	{
	  poly_dim_t x = px, y = py;
	  poly_order (s->extrude[e], &x, &y);
	  plot_loops (s->extrude[e], sp, flowrate, 0, &p);
	}
      plot_loops (s->extrude[e], speed0, flowrate, -1, &p);	// flying layer - in order it was made
      plot_loops (s->extrude[e], speed0, flowrate, 1, &p);	// flying layer - in order it was made
      if (s == stl->slices && temp && temp0 != temp)
	{
	  //move (cx, cy, z + hop * 2, back);
	  //fprintf (o, "M109 S%d\n", temp);
	  fprintf (o, "M108 S%d\n", temp);
	}
      z += layer;
      s = s->next;
      sp = speed;
    }
  move (px, py, z + hop, back, speed, &p);
  move (cx, cy, z + hop, back, speed, &p);
  move (cx, cy, z + layer * 10, back, speed, &p);
  move (cx, cy, z + layer * 20, 0, speed, &p);
  // post
  fprintf (o,			//
	   "M108 S0         ; Cold hot end\n"	//
	   "M140 S0         ; Cold bed\n"	//
	   "M084            ; Disable steppers\n"	//
	   "M107            ; fan off\n"	//
    );
  fclose (o);
  if (!quiet)
    printf ("Filament used %.0Lf\n", pe);
  return t / 1000000LL;
}
