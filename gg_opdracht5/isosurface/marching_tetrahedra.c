/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name .... Sharon Gieske & Ysbrand Galama
 * Student email ... sharongieske@gmail.com & y.galama@hotmail.com
 * Collegekaart .... 6167667 & 10262067
 * Date ............ 17/03/2013
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "marching_tetrahedra.h"

/* Compute a linearly interpolated position where an isosurface cuts
   an edge between two vertices (p1 and p2), each with their own
   scalar value (v1 and v2) */

static vec3
interpolate_points(unsigned char isovalue, vec3 p1, vec3 p2, unsigned char v1, unsigned char v2)
{
    /* Initially, simply return the midpoint between p1 and p2.
       So no real interpolation is done yet */

    return v3_add(v3_multiply(p1, 0.5), v3_multiply(p2, 0.5));
}

/* Using the given iso-value generate triangles for the tetrahedron
   defined by corner vertices v0, v1, v2, v3 of cell c.

   Store the resulting triangles in the "triangles" array.

   Return the number of triangles created (either 0, 1, or 2).

   Note: the output array "triangles" should have space for at least
         2 triangles.
*/

static int
generate_tetrahedron_triangles(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3)
{
	/* SLIDES:
	Thetrahedon is an object consisting of 4 vertices, 6 edges that span 4 faces
	*/

	int bitvalue[4];
	// TODO wat is v0?? de index? de waarde van de vertices?
	// set bitvalues of vertices:
	if (c.value[v0] <= isovalue) bitvalue[0] = 0; else bitvalue[0] = 1;
	if (c.value[v1] <= isovalue) bitvalue[1] = 0; else bitvalue[1] = 1;
	if (c.value[v2] <= isovalue) bitvalue[2] = 0; else bitvalue[2] = 1;
	if (c.value[v3] <= isovalue) bitvalue[3] = 0; else bitvalue[3] = 1;

	/* Cases of 1 triangle:*/
	// case of 0001 or 1110
	if(bitvalue[1] == bitvalue[2] && bitvalue[2] == bitvalue[3] && bitvalue[0] != bitvalue[1])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        return 1;
    }
	// case of 0010 or 1101
	if(bitvalue[0] == bitvalue[2] && bitvalue[2] == bitvalue[3] && bitvalue[0] != bitvalue[1])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v1], c.p[v0], c.value[v1], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        return 1;
    }
	// case of 0100 or 1011
	if(bitvalue[0] == bitvalue[1] && bitvalue[1] == bitvalue[3] && bitvalue[0] != bitvalue[2])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v2], c.p[v1], c.value[v2], c.value[v1]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        return 1;
    }
	// case of 1000 or 0111
	if(bitvalue[0] == bitvalue[1] && bitvalue[1] == bitvalue[2] && bitvalue[0] != bitvalue[3])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v3], c.p[v0], c.value[v3], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v3], c.p[v1], c.value[v3], c.value[v1]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v3], c.p[v2], c.value[v3], c.value[v2]);
        return 1;
    }

	/* Cases of 2 triangles:*/
	// case of 0011 or 1100
    if(bitvalue[0] == bitvalue[1] && bitvalue[2] == bitvalue[3] && bitvalue[0] != bitvalue[2])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v1], c.p[v0], c.value[v1], c.value[v0]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        return 2;
    }
	// case of 0101 or 1010
    if(bitvalue[0] == bitvalue[2] && bitvalue[1] == bitvalue[3] && bitvalue[0] != bitvalue[1])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v2], c.p[v1], c.value[v2], c.value[v1]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        return 2;
    }
	// case of 1001 or 0110
    if(bitvalue[0] == bitvalue[3] && bitvalue[1] == bitvalue[2] && bitvalue[0] != bitvalue[1])
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v3], c.p[v0], c.value[v3], c.value[v0]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v3], c.p[v1], c.value[v3], c.value[v1]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v3], c.p[v2], c.value[v3], c.value[v2]);
        return 2;
	}
	// Case of zero triangles (0000 or 1111) 
    return 0;
}

/* Generate triangles for a single cell for the given iso-value. This function
   should produce at most 6 * 2 triangles (for which the "triangles" array should
   have enough space).

   Use calls to generate_tetrahedron_triangles().

   Return the number of triangles produced
*/

int
generate_cell_triangles(triangle *triangles, cell c, unsigned char isovalue)
{
    int triangles = 0;
	// Indices for tertrahedron
	int a[6] = {1, 2, 4, 1, 2, 4};
	int b[6] = {3, 6, 5, 5, 3, 6};

	// Loop through all 6 possible tetrahedron
	for(int i = 0; i < 6; i++){
		triangles += generate_tetrahedron_triangles(&triangles[tri], isovalue, c, 0, a[i], b[i], 7);
	}

    return triangles;
}
