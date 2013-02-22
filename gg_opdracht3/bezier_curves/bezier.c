/* Computer Graphics, Assignment, Bezier curves
 *
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name .... Sharon Gieske & Ysbrand Galama
 * Student email ... sharongieske@gmail.com & y.galama@hotmail.com
 * Collegekaart .... 6167667 & 10262067
 * Date ............ 22/02/2013
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>
#include <stdlib.h>




/* Calculate factorial
 */
int
fact(int fac){
	int temp = 1;
	for(int i = 1; i <= fac; i++){
		temp *= i;
	}
	return temp;
}

/* Calculate binomial distribution 
 */
float
binomial(int i, int num_points){
	return (float)fact(num_points) / (float)(fact(i) * fact(num_points-i));
}

/* Calculate Bernstein basis polynomials
 */
float
bernstein(int i, int num_points, float u){
	return binomial(i,num_points) * (float)pow(u,i) * (float)pow((1-u),(num_points-i));
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */
void
evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u)
{
	*x = 0.0;
	*y = 0.0;
	// Loop for sum	
	for(int i = 0; i < num_points; i++){
		float temp;
		temp = bernstein(i,num_points-1,u);

		// change x and y coordinates
		*x += (temp * p[i].x);
		*y += (temp * p[i].y);
		}


}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void
draw_bezier_curve(int num_segments, control_point p[], int num_points)
{

	float *x,*y;
	x = malloc(sizeof(float));
	y = malloc(sizeof(float));
	glBegin(GL_LINE_STRIP);

	// start point of line
	glVertex2f(p[0].x, p[0].y);

	// draw lines for curve
	for(int i=1; i < num_segments; i++){
		// compute point
		evaluate_bezier_curve(x, y, p, num_points, (float)i / (float)num_segments );
		// draw line to next point
		glVertex2f(*x,*y);
	}
	// end point of line
	glVertex2f(p[num_points-1].x, p[num_points-1].y);
	glEnd();

}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/


float // calculate the root of a cubic function (formulas from http://en.wikipedia.org/wiki/Cubic_function)
abcd(float a, float b, float c, float d)
{
	float D,Q,C, p,q;
	
	p = 2*b*b*b - 9*a*b*c + 27*a*a*d;
	q = b*b - 3*a*c;
	
	Q = sqrt(p*p - 4*q*q*q);
	C = cbrtf( (Q+p)/2 );
	
	if (Q==0 && q==0)
		return -b/ 3/a;

	else if (Q!=0 && q==0 && C==0)
		C = cbrtf((-Q + p) / 2);
	return -b/ 3/a - C/ 3/a - q/ 3/a/C;
}

float // calculate the root of a quadratic function
abc(float a, float b, float c)
{
	float d,xa,xb;

	d = b*b - 4*a*c;
	
	xa = -b - sqrt(d)/ 2/a;
	xb = -b + sqrt(d)/ 2/a;

	return xa;
}

float // calculate the root of a linear function
ab(float a, float b)
{
	return -b/a;
}

int
intersect_cubic_bezier_curve(float *y, control_point p[], float x)
{
	if (p[0].x < x && x < p[3].x)
	{
		float a,b,c,d, r,q, u;

		// set parameters for calculation
		a = -p[0].x + 3*p[1].x - 3*p[2].x + p[3].x;
		b = 3*p[0].x - 6*p[1].x + 3*p[2].x;
		c = -3*p[0].x + 3*p[1].x;
		d = p[0].x - x;
		
		// use correct function to calculate u for given x
		if (a!=0)
			u = abcd(a,b,c,d);
		else if (b!=0)
			u = abc(b,c,d);
		else if (c!=0)
			u = ab(c,d);
		else
			u = d;
		if (isnan(u))
			return 0;
		// calculate y form u
		*y = ( -p[0].y + 3*p[1].y - 3*p[2].y + p[3].y ) *u*u*u 
			+ ( 3*p[0].y - 6*p[1].y + 3*p[2].y ) *u*u
			+ ( -3*p[0].y + 3*p[1].y ) *u
			+ ( p[0].y );
		
		return 1;
	}
	return 0;
}

