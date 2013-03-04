/* Computer Graphics and Game Technology, Assignment Ray-tracing
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
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
	float intensity,tmp,zero;
	zero = 0.0001;
	vec3 temp = v3_create(0,0,0);
	
	// ambient light everywhere
	intensity = scene_ambient_light;
	
	// calculate intensity from all ligths
	for (int i=0; i<scene_num_lights; ++i)
	{
		// Only increase light intensity if no object in way between point and lightsource
		if(shadow_check(v3_add(ip.p,v3_multiply(ip.n,zero)), scene_lights[i].position) == 0){

			temp = v3_subtract(scene_lights[i].position, ip.p);
			// vector scale by intensity
			temp = v3_normalize(temp);
			temp = v3_multiply(temp,scene_lights[i].intensity);
		
			tmp = v3_dotprod( temp, ip.n);

			// only increase if light in direction
			if (tmp > 0)
				intensity += tmp;
		}
	}
	
	// intensity cannot be greater than 1
	if (intensity > 1)
		intensity = 1;
		
	return v3_create(intensity,intensity,intensity);
}

vec3
shade_blinn_phong(intersection_point ip)
{
	// constants
	float kd, ks, alpha,zero;
	kd = 0.8;
	ks = 0.5;
	alpha = 50;
	zero = 0.0001;
	
	vec3 cd, cs;
	cd = v3_create(1,0,0);
	cs = v3_create(1,1,1);
	vec3 temp = v3_create(0,0,0);
	vec3 temp_highlight = v3_create(0,0,0);

	//final surface color cf
	float intensity, highlight,  tmp;

	intensity = 0;
	highlight = 0;
	// calculate intensity from all ligths
	for (int i=0; i<scene_num_lights; ++i){
		if(shadow_check(v3_add(ip.p,v3_multiply(ip.n,zero)), scene_lights[i].position) == 0){

			temp = v3_subtract(scene_lights[i].position, ip.p);
			// vector scale by intensity
			temp = v3_normalize(temp);
			
			// Phong shader sum
			temp_highlight = v3_multiply( 
								v3_add(ip.i, temp), 
								1/(v3_length(
									v3_add(ip.i, temp))));
			
			highlight += scene_lights[i].intensity * pow(v3_dotprod( temp_highlight, ip.n),alpha);
			
			// light sum
			temp = v3_multiply(temp,scene_lights[i].intensity);
			tmp = v3_dotprod( temp, ip.n);

			// only increase if light in direction
			if (tmp > 0)
				intensity += tmp;

		}
	}
	
	return v3_add(
					v3_multiply(cd, (scene_ambient_light + kd * intensity) ),
					v3_multiply(cs, ks * highlight) );
}

vec3 // TODO: werkt bijna, maar puntjes op spheres zijn terug...
shade_reflection(intersection_point ip)
{
    float refpart,zero;
    refpart = 0.25;
   	zero = 0.0001;
    
    vec3 ray, color;

    ray = v3_subtract( v3_multiply(ip.n, 2 * v3_dotprod(ip.i, ip.n)), ip.i);
    color = ray_color( ip.ray_level+1, v3_add(ip.p,v3_multiply(ip.n,zero)), ray);
    
    
    return v3_add(
    		v3_multiply(shade_matte(ip), 1.0 - refpart),
    		v3_multiply(color,refpart));
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
  switch (ip.material)
  {
    case 0:
      return shade_constant(ip);
    case 1:
      return shade_matte(ip);
    case 2:
      return shade_blinn_phong(ip);
    case 3:
      return shade_reflection(ip);
    default:
      return shade_constant(ip);

  }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
    intersection_point  ip;

    // If this ray has been reflected too many times, simply
    // return the background color.
    if (level >= 3)
        return scene_background_color;

    // Check if the ray intersects anything in the scene
    if (find_first_intersection(&ip, ray_origin, ray_direction))
    {
        // Shade the found intersection point
        ip.ray_level = level;
        return shade(ip);
    }

    // Nothing was hit, return background color
    return scene_background_color;
}
