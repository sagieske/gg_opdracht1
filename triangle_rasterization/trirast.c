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

void
draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
	PutPixel(x0, y0, r, g, b);
	PutPixel(x1, y1, r, g, b);
	PutPixel(x2, y2, r, g, b);



}

void
draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
	PutPixel(x0, y0, r, g, b);
	PutPixel(x1, y1, r, g, b);
	PutPixel(x2, y2, r, g, b);


}
