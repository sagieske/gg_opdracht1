/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
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

#include "SDL.h"   
#include "init.h"

/*
 * Midpoint Line Algorithm
 *
 * As you probably will have figured out, this is the part where you prove
 * your programming skills. The code in the mla function should draw a direct 
 * line between (x0,y0) and (x1,y1) in the specified color. 
 * 
 * Until now, the example code below draws only a horizontal line between
 * (x0,y0) and (x1,y0) and a vertical line between (x1,y1).
 * 
 * And here the challenge begins..
 *
 * Good luck!
 *
 *
 */
void mla(SDL_Surface *s, int x0i, int y0i, int x1i, int y1i, Uint32 colour) {
  //int ix,iy;
	
	double x,y;

	double x0 = x0i;
	double x1 = x1i;
	double y0 = y0i;
	double y1 = y1i;
	PutPixel(s,x0,y0,colour);
	PutPixel(s,x1,y1,colour);

	y = y0;
	for (x = x0; x<x1; ++x)
	{
		PutPixel(s,x,y,colour);
		if (((y0-y1)*(x+1)+(x1-x0)*(y-0.5)+x0*y1-x1*y0) > 0)
			y--;
		
	}
	return;
}

