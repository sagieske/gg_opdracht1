/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "types.h"

/*
 * Rasterize a single triangle.
 * The triangle is specified by its corner coordinates
 * (x0,y0), (x1,y1) and (x2,y2).
 * The triangle is drawn in color (r,g,b).
 */

/*TODO: Problemen: 
*	berekening met offscreen point doet gek, bijna geen gedeelde punten meer, maar op lijn liggen nu zwarte vlakken
*	heel soms nog eens een punt wat dubbel getekent wordt in de d-mode
*/

// Offscreen point
float off_x = -1;
float off_y = -1;


float min(float a, float b, float c)
{
	float m = a;
	if (m > b) m = b;
	if (m > c) m = c;
	return m;
}

float max(float a, float b, float c)
{
	float m = a;
	if (m < b) m = b;
	if (m < c) m = c;
	return m;
}

float
formula(float x0, float y0, float x1, float y1, float x2, float y2) {
	float result =  (y0 - y1)*x2+(x1-x0)*y2+x0*y1-x1*y0;
	return result;
}

void
draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
	float xmin,xmax,ymin,ymax;
	float f20,f01, f12;
	float alpha,beta,gamma;
	float x,y;
	float off_f12, off_f20, off_f01;
	xmin = min(x0,x1,x2);
	xmax = max(x0,x1,x2);
	ymin = min(y0,y1,y2);
	ymax = max(y0,y1,y2);
	
	f20 = formula(x2,y2, x0, y0, x1, y1);
	f01 = formula(x0,y0, x1, y1, x2, y2);
	f12 = formula(x1,y1, x2, y2, x0, y0);

	// calculations for offscreen point
 	off_f12 = formula(x1,y1, x2, y2, off_x, off_y);
	off_f20 = formula(x2,y2, x0, y0, off_x, off_y);
	off_f01 = formula(x0,y0, x1, y1, off_x, off_y);

	for (x = xmin; x < xmax; ++x)
	{
		for (y = ymin; y < ymax; ++y)
		{
			beta  = ( (y2 - y0)*x+(x0-x2)*y+x2*y0-y2*x0 ) / f20;
			gamma = ( (y0 - y1)*x+(x1-x0)*y+x0*y1-x1*y0 ) / f01;
			alpha = 1 - beta - gamma;
			//if (0<=alpha && alpha<=1 && 0<=beta && beta<=1 && 0<=gamma && gamma<=1)
			//PutPixel(x,y,r,g,b);

			// code from book on pixels sharing edge
			if (alpha >= 0 && beta >= 0 && gamma >= 0){
				if((alpha > 0 || (f12*off_f12) > 0) && (beta > 0 || (f20*off_f20) > 0) && (gamma > 0 || (f01*off_f01) > 0)){
					PutPixel(x,y,r,g,b);
				}
			}			

		}
	}
	
}

void
draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{

	printf("%f,%d",x0+x1+x2+y0+y1+y2,r+g+b);
}
