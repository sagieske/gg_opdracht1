/* Computer Graphics, Assignment 5, Orthogonal projection
 *
 * Filename ........ ortho.c
 * Description ..... Contains the re-programmed orthogonal projection matrix
 * Date ............ 01.09.2006
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

 
#define sqr(x) ((x)*(x))

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myOrtho(GLdouble left,
             GLdouble right,
             GLdouble bottom,
             GLdouble top,
             GLdouble near,
             GLdouble far) {
             
    GLdouble M[16] = {
    	2.0 / (right - left) , 0 , 0 , 0,
    	0 , 2.0 / (top - bottom) , 0 , 0,
    	0 , 0 ,  2.0 / (near - far)  , 0,
    	-(right+left)/(right-left), -(top+bottom)/(top-bottom), -(near+far)/(near-far), 1
    };
    
    glMultMatrixd(&M[0]);

}
