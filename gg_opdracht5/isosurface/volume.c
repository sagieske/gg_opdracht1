/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name .... Sharon Gieske & Ysbrand Galama
 * Student email ... sharongieske@gmail.com & y.galama@hotmail.com
 * Collegekaart .... 6167667 & 10262067
 * Date ............ 14/03/2013
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdio.h>
#include <stdlib.h>

#include "volume.h"

/* The voxels of the volume dataset, stored as a one-dimensional array */
unsigned char   *volume;

/* The dimensions of the volume dataset */
int     nx, ny, nz;

/* The size of a voxel */
float   sizex, sizey, sizez;

/* Utility function to convert the index of a voxel
   into an index in the volume array above */
int
voxel2idx(int i, int j, int k)
{
    return (k*ny + j)*nx + i;
}

/* Extract a cell from the volume, so that datapoint 0 of the
   cell corresponds to voxel (i, j, k), datapoint 1 to voxel (i+1, j, k),
   etc. See the assignment. */
cell
get_cell(int i, int j, int k)
{
	// Get index from voxel
	//int index = voxel2idx(i,j,k);
    cell c;// = volume[index];
    int is[8] = {0,0,0,0,1,1,1,1};
    int js[8] = {0,0,1,1,0,0,1,1};
    int ks[8] = {0,1,0,1,0,1,0,1};
    for (int q=0; q < 8; ++q)
    	c.p[i] = v3_create(i+is[i],j+js[i],k+ks[i]);
    return c;
}

/* Utility function to read a volume dataset from a VTK file.
   This will store the data in the "volume" array and update the dimension
   and size values. */

void
read_volume(const char *fname)
{
    FILE *f;
    char s[256];
    int nvoxels;

    printf("Reading %s\n", fname);
    f = fopen(fname, "rb");

    if (!f)
    {
        fprintf(stderr, "read_volume(): Could not open file '%s' for reading!\n", fname);
        exit(-1);
    }

    // header line
    fgets(s, 255, f);

    // comment line
    fgets(s, 255, f);

    // BINARY
    fgets(s, 255, f);

    // DATASET STRUCTURED_POINTS
    fgets(s, 255, f);

    // DIMENSIONS %d %d %d
    fscanf(f, "%s %d %d %d\n", s, &nx, &ny, &nz);
    printf("%d x %d x %d voxels\n", nx, ny, nz);

    // ASPECT_RATIO/SPACING %f %f %f
    fscanf(f, "%s %f %f %f\n", s, &sizex, &sizey, &sizez);
    printf("voxel sizes: %.3f, %.3f, %.3f\n", sizex, sizey, sizez);

    // ORIGIN ...
    fgets(s, 255, f);

    // POINT_DATA ...
    fgets(s, 255, f);

    // SCALARS ...
    fgets(s, 255, f);

    // LOOKUP_TABLE ...
    fgets(s, 255, f);

    // allocate memory to hold the volume data and read it from file
    nvoxels = nx * ny * nz;
    volume = (unsigned char*)malloc(nvoxels);

    if (fread(volume, 1, nvoxels, f) < (size_t)nvoxels)
    {
        printf("WARNING: not all data could be read!\n");
    }

    fclose(f);
}
