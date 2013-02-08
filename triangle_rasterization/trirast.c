/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name .... Sharon Gieske & Ysbrand Galama
 * Student email ... sharongieske@gmail.com & y.galama@hotmail.com
 * Collegekaart .... 6167667 & 10262067
 * Date ............ 8/02/2013
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


// Offscreen point
float off_x = -1;
float off_y = -1;

/* Function to calculate minimal float of 3 floats
*/
float min(float a, float b, float c)
{
	float m = a;
	if (m > b) m = b;
	if (m > c) m = c;
	return m;
}

/* Function to calculate maximal float of 3 floats
*/
float max(float a, float b, float c)
{
	float m = a;
	if (m < b) m = b;
	if (m < c) m = c;
	return m;
}

/* Formula for line
*/
float
formula(float x0, float y0, float x1, float y1, float x2, float y2) {
	float result =  (y0 - y1)*x2+(x1-x0)*y2+x0*y1-x1*y0;
	return result;
}

/* Triangle rasterization algorithm
*/
void
draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
	float xmin,xmax,ymin,ymax;
	float f20,f01, f12;
	float alpha,beta,gamma;
	float x,y;
	float off_f12, off_f20, off_f01;

	//square around triangle in which all points are looked at
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


	// Loop through square and check if pixel is in triangle
	for (x = xmin; x <= xmax; ++x)
	{
		for (y = ymin; y <= ymax; ++y)
		{

			beta  = ( (y2 - y0)*x+(x0-x2)*y+x2*y0-y2*x0 ) / f20;
			gamma = ( (y0 - y1)*x+(x1-x0)*y+x0*y1-x1*y0 ) / f01;
			alpha = ( (y1 - y2)*x+(x2-x1)*y+x1*y2-x2*y1 ) / f12;

			// Pixel is in triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0){
				if((alpha > 0 || (f12*off_f12) >= 0) && (beta > 0 || (f20*off_f20) > 0) && (gamma > 0 || (f01*off_f01) > 0)){
					PutPixel(x,y,r,g,b);
				}
			}		
		}
	}
	
}

/* Triangle rasterization algorithm with optimizations
*/
void
draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
	float xmin,xmax,ymin,ymax;
	float f20,f01, f12;
	float alpha,beta,gamma;
	float x,y;
	float off_f12, off_f20, off_f01;
	float x02,x10, x21, y20,y01, y12;
	
	//square around triangle in which all points are looked at
	xmin = min(x0,x1,x2);
	xmax = max(x0,x1,x2);
	ymin = min(y0,y1,y2);
	ymax = max(y0,y1,y2);
	
	f20 = formula(x2,y2, x0, y0, x1, y1);
	f01 = formula(x0,y0, x1, y1, x2, y2);
	f12 = formula(x1,y1, x2, y2, x0, y0);
	
	x02 = (x0-x2)/f20;
	x10 = (x1-x0)/f01;
	x21 = (x2-x1)/f12;

	y20 = (y2-y0)/f20;
	y01 = (y0-y1)/f01;
	y12 = (y1-y2)/f12;

	// calculations for offscreen point
 	off_f12 = formula(x1,y1, x2, y2, off_x, off_y);
	off_f20 = formula(x2,y2, x0, y0, off_x, off_y);
	off_f01 = formula(x0,y0, x1, y1, off_x, off_y);
	
	beta  = ( (y2 - y0)*xmin+(x0-x2)*ymin+x2*y0-y2*x0 ) / f20;
	gamma =	( (y0 - y1)*xmin+(x1-x0)*ymin+x0*y1-x1*y0 ) / f01;
	alpha = ( (y1 - y2)*xmin+(x2-x1)*ymin+x1*y2-x2*y1 ) / f12;

	
	// Loop through square and check if pixel is in triangle
	for (x = xmin; x < xmax; ++x)
	{	
		for (y = ymin; y < ymax; ++y)
		{
			
			// Pixel is in triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0){
				if((alpha > 0 || (f12*off_f12) > 0) && (beta > 0 || (f20*off_f20) > 0) && (gamma > 0 || (f01*off_f01) > 0)){
					PutPixel(x,y,r,g,b);
				}
			}
			beta  += x02;
			gamma += x10;
			alpha += x21;
		}
		beta  += y20 -(ymax-ymin)*x02;
		gamma += y01 -(ymax-ymin)*x10;
		alpha += y12 -(ymax-ymin)*x21;
	}
}
