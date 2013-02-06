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
void swap_int(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void swap_double(double* a,double* b)
{
	double t=*a;
	*a=*b;
	*b=t;
}

void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
    //int ix,iy;
	
	double x,y;
	double dx, dy;
	double diff; 
	
	dx = x1 - x0;
	dy = y1- y0;
	diff = dx/dy;
	printf("diff : %f\n", diff);


	printf("dx %f, dy %f", dx, dy);

	if(x0 > x1 && y0 < y1){
		swap_int(&x0, &x1);
		swap_int(&y0, &y1);
	}

	PutPixel(s,x0,y0,colour);
	PutPixel(s,x1,y1,colour);

	if( diff >= 0 && diff <= 1) {
		y = y0;
		for (x = x0; x<x1; ++x)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)((y0-y1)*(x-1))+(double)(x1-x0)*(y+0.5)+(double)(x0*y1)-(double)(x1*y0));
			if (d > 0)
				y--;
		}
	} else if (diff > 1){
		x = x0;
		for (y = y0; y>y1; --y)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)((y0-y1)*(x+0.5))+(double)(x1-x0)*(y-1)+(double)(x0*y1)-(double)(x1*y0));
			if (d < 0)
				x++;
		
		}
	} else if ( diff < 0 && diff > -1 ) {
		printf("rc is [0,-1]");
		y = y0;
		for (x = x0; x<x1; ++x)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)(-(y0-y1)*(x-1))-(double)(x1-x0)*(y-0.5)-(double)(x0*y1)+(double)(x1*y0));
			if (d > 0)
				y++;
		}
	} else { 
		printf("rc is [-1,-inf]");	
	}












	if (abs(dy) > abs(dx)) {
	x = x0;
		for (y = y0; y>y1; --y)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)((y0-y1)*(x+0.5))+(double)(x1-x0)*(y-1)+(double)(x0*y1)-(double)(x1*y0));
			if (d < 0)
				x++;
		
		}
	} else {
		y = y0;
		for (x = x0; x<x1; ++x)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)((y0-y1)*(x-1))+(double)(x1-x0)*(y+0.5)+(double)(x0*y1)-(double)(x1*y0));
			if (d > 0)
				y--;
		}
	}
		return;
}



