/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
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

/* Swap function to swap a and b using pointers. Function used for integers.
*/
void swap_int(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

/* Swap function to swap a and b using pointers. Function used for doubles.
*/
void swap_double(double* a,double* b)
{
	double t=*a;
	*a=*b;
	*b=t;
}

/* Midpoint Line Algorithm to draw line between (x0, y0) and (x1, y1)
*/
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
	double x,y;
	double dx, dy;
	double diff; 
	double sign;

	// swap points to mirror lines on y-axis
	if(x0 > x1){
		swap_int(&x0, &x1);
		swap_int(&y0, &y1);
	}

	dx = x1 - x0;
	dy = y1 - y0;
	diff = dy/dx;	// slope

	sign = 1;		// set sign for later formula

	// Color end points of line, are fixed given as function parameters
	PutPixel(s,x0,y0,colour);
	PutPixel(s,x1,y1,colour);
	
	// slope between -1 and inf
	if( (-1 <= diff && diff < 0) ||  (diff >= 0 && diff < 1 ) || (diff >=1)) {
		// flip over x-axis		
		if (diff >= 1){
			swap_double(&x,&y);
			swap_int(&x0, &y0);
			swap_int(&x1, &y1);
			sign = -1;
		}	

		// take steps over y-axis				
		y = y0;
		for (x = x0; x<x1; ++x)
		{
			// flip sign when 0 <= slope < 1
			if(diff >= 0 && diff < 1 )
				sign = -1;

			// flip x, y coordinates for pixel drawing since x,y coordinates were swapt for formula
			if( diff >= 1)
				PutPixel(s,y,x,colour);
			else
				PutPixel(s,x,y,colour);

			// Midpoint calculation
			double d = sign*((double)((y0-y1)*(x-1))+(double)(x1-x0)*(y+0.5)+(double)(x0*y1)-(double)(x1*y0));	

			// Compare line to midpoint and determine direction of next coordinate
			if (d > 0)
				y -= sign;
			if (d < 0 && diff > 1 )
				y += sign;
		}
	} 	
	//	slope between -inf and -1
	else {
		x = x0;
		for (y = y0; y>y1; --y)
		{
			PutPixel(s,x,y,colour);
			double d = ((double)((y0-y1)*(x-0.5))+(double)(x1-x0)*(y-1)+(double)(x0*y1)-(double)(x1*y0));
			if (d < 0)
				x++;
		}
	} 
	return;
	/* Code van internet
	double dy,dx;
 	double x,y;
 	double p,p0,dp1,dp2;

 	dy = y0-y1;
	dx = x0-x1;

	p0 = 2 * (dy - dx);
	dp1 = 2 * dy;
	dp2 = 2 * (dy - dx);

	PutPixel(s,x1,y1,colour);
	p = p0;

	for(x=x1+1,y=y1;x<x0;x++)
		{
		 if(p < 0)
		 {
		  p = p+dp1;
		  PutPixel(s,x,y,colour);
		 }
		 else
		 {
		  p = p+dp2;
		  y++;
		  PutPixel(s,x,y,colour);
		 }
     }
     return;
     */
}



