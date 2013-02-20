/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
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
	return fact(num_points) / (fact(i) * fact(num_points-i));
}

/* Calculate Bernstein basis polynomials
 */
float
bernstein(int i, int num_points, float u){
	return binomial(i,num_points) * pow(u,i) * pow((1-u),(num_points-i));
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

	printf("HELLO\n");
	// Loop for sum	
	for(int i = 0; i <= num_points; i++){
		float temp;
		temp = bernstein(i,num_points,u);
		// change x and y coordinates
		*x += temp * p[i].x;
		*y += temp * p[i].y;
		}
	printf("x: %f, y: %f", *x, *y);

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
	printf("HELLO\n");

	printf("%e, %e \n",p[0].x,p[0].y);
	// set up points
	*x =  p[0].x;
	*y =  p[0].y;
	printf("JAaaa");

	//TODO: SEGMENTATION FAULT

	for(int i=0; i < num_segments; i++){
		// compute point

		evaluate_bezier_curve(x, y, p, num_points, i);

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

int
intersect_cubic_bezier_curve(float *y, control_point p[], float x)
{
    return 0;
}

