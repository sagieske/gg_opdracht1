/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 *
 * Student name .... Sharon Gieske & Ysbrand Galama
 * Student email ... sharongieske@gmail.com & y.galama@hotmail.com
 * Collegekaart .... 6167667 & 10262067
 * Date ............ 15/02/2013
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

 
/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif


/* Function to calculate dotproduct between two vectors
*/
GLfloat dot(GLfloat u[3], GLfloat v[3])
{
	GLfloat ans;
	ans = u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
	return ans;
}

/* Function to calculate crossproduct between two vectors
*/
// cross(&ans[0], v1, v2)
void cross(GLfloat *ans, GLfloat u[3], GLfloat v[3])
{
	ans[0] = u[1]*v[2]-u[2]*v[1];
	ans[1] = u[2]*v[0]-u[0]*v[2];
	ans[2] = u[0]*v[1]-u[1]*v[0];
}
/* Function to normalize vector
*/
void normalize(GLfloat *vector){
	GLfloat vec[3] = {vector[0],vector[1],vector[2]};
 	GLfloat length =  sqrt(dot(vec, vec));
	vector[0] = vector[0] / length;
	vector[1] = vector[1] / length;
	vector[2] = vector[2] / length;
}

void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {
	// NOTES:
	// ViewReferencePoint = eye
	// ProjectionReferencePoint = center
	// DirectionOfProjection = up
	GLfloat vrf[3] = {eyeX, eyeY, eyeZ};
	GLfloat prp[3] = {centerX, centerY, centerZ};
	GLfloat up[3] = {upX, upY, upZ};

	//A translation by −VRP (eye coordinates)
	glTranslatef(-eyeX,-eyeY,-eyeZ);

	// TODO: A coordinate system change to camera coordinates. 
    GLfloat M[16] =
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

	GLfloat cx[3], cy[3], cz[3];

	// cz = vector pointing from Pcamera to PlookAt .
	cz[0] = centerX - eyeX;
	cz[1] = centerY - eyeY;
	cz[2] = centerZ - eyeZ;
	normalize(&cz[0]);

	// cx = up x cz and normalize cx	
	cross(&cx[0], up, cz);
	normalize(&cx[0]);

	// cy vector simply is orthogonal to both cx and cz, already normalized
	cross(&cy[0], cx, cz);

	// Rotation matrix R that produces world coordinates when camera coordinates are given:
	GLfloat R[3];
	R[0] = cx[0]*cx[1]-cx[2];
	R[1] = cy[0]*cy[1]-cy[2];
	R[2] = cz[0]*cz[1]-cz[2];

	// TODO: Transposed rotation matrix R ?? 



}
