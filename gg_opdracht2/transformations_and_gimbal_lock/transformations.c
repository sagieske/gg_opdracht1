/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.c
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "transformations.h"

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myScalef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(M);
}


void myTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    };

    glMultMatrixf(M);
}
/* Function to calculate dotproduct between two vectors
*/
GLfloat dot(GLfloat u[3], GLfloat v[3])
{
	GLfloat ans;
	ans = u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
	return ans;
}



GLfloat makeT(GLfloat *t, GLfloat w[3])
{
	int i=0;
	if (w[i] > w[1])
		i=1;
	if (w[i] > w[2])
		i=2;
	t[0] = w[0];
	t[1] = w[1];
	t[2] = w[2];
	t[i] = 1;
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

void printVector(GLfloat *vector){
	printf("Vector: [%f, %f, %f]\n", vector[0],vector[1],vector[2]);  
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

void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat u[3], v[3], t[3];

    //
    // 1. Create the orthonormal basis

    // Store the incoming rotation axis in w and 
 	GLfloat w[3] = {x,y,z};

	// Normalize w
	normalize(&w[0]);

    // Compute the value of t, based on w
	makeT(&t[0], w);

    // Compute u = t x w
	cross(&u[0], t, w);

    // Normalize u
	normalize(&u[0]);

	// Compute v = w x u
	cross(&v[0],w,u);

    // At this point u, v and w should form an orthonormal basis.
    // If your routine does not seem to work correctly it might be
    // a good idea to the check the vector values.
	
	/*	Check is correct
	GLfloat u_in =  sqrt(dot(u, u));
	GLfloat v_in =  sqrt(dot(v, v));
	GLfloat w_in =  sqrt(dot(w, w));
	GLfloat uv_in =  sqrt(dot(u, v));
	GLfloat vw_in =  sqrt(dot(v, w));
	GLfloat wv_in =  sqrt(dot(w, v));
	// U, V and W calculated correctly. Inproduct with self is 1 
	printf("Inproduct with other: uv = %f, vw = %f, wv =%f\n", uv_in, vw_in, wv_in);
	printf("Inproduct with self: u = %f, v = %f, w =%f\n", u_in, v_in, w_in);
	*/

    //
    // 2. Set up the three matrices making up the rotation
    //
    // Specify matrix A


    GLfloat A[16] =
    {
        u[0], u[1], u[2], 0.0,
        v[0], v[1], v[2], 0.0,
     	w[0], w[1], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    // Convert 'angle' to radians

    // Specify matrix B

    GLfloat B[16] =
    {
        cos(angle), sin(angle), 0.0, 0.0,
        -sin(angle), cos(angle), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    // Specify matrix C

    GLfloat C[16] =
    {
		u[0], v[0], w[0], 0.0,
        u[1], v[1], w[1], 0.0,
     	u[2], v[2], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0

    };

    //
    // 3. Apply the matrices to get the combined rotation
    //

    glMultMatrixf(A);
    glMultMatrixf(B);
    glMultMatrixf(C);
}

