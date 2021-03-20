/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/20 22:32:35 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Psuedo code for a raytracing algorithm


// what is the relationship of the camera to the  raster
// define ypsilon 1e-6

t_ray	ft_build_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	printf("entering ray builder\n");
	// To calculate a ray you need:
	// The ray origin(from camera) (O), ray direction (from args) (R) , and a point (P) along the ray [x, y]
	// P = O + tR  (t = distance from origin to the point)
	// tan a = opposite_side / ajacent_side
	// ray.origin = cam->vect_coords;
	// ray.direction.x = x;
	// ray.direction.y = y;

	return (ray);
}

int		ft_intersect(t_ray ray, void *shape_list, unsigned int *col, float *nearest)
{
	// For the parametric I = R(t) = (1 - t)C +tP
	// Where:  I = Intersection
			// t = weighted average (check formula)
		   	// C = camera coords
		   	// P = Pixel, in pixelgrid coords
	// You have C[x,y,z] and P[x,y, z(with the tangient of FOV)]
	// t needs to be calculated for each point encountered ex.
			// Ix = Rx(t) = (1 - t)Cx + tPx
			// Iy = Ry(t) = (1 - t)Cy + tPy
			// Iz = Rz(t) = (1 - t)Cz + tPz

			// Then substitute the above into the line equation: Ax + By +Cz + D = 0;
	return (1);
}

int		ft_tracer(int x, int y, t_env *env)
{
	int p = 0;
	int r = 0;
	float nearest = INFINITY;
	unsigned int color = 0;
	t_ray	ray;

	x -= env->res.x / 2;
	y = (env->res.y / 2) - y;
	// First compute primary ray direction
	ray = ft_build_ray((t_camera*)(env->cam_list), x, y);
	// printf("Entering tracer\n");
	while (p < TRIANGLE)
	{
		// while (r < env->shapes[p] ) // add number of triangels??????
		// // maybe necesary to add another loop for the mount of triangles in the object
	
		// Shoot primary ray in the scene in search for an intersection
		// in my intersect, iterate over all shapes
		// my_lstiter(env->shapes[i], img, (void*)ft_draw_square);
		// also triangle intersect for each triangel in the shape
		if(ft_intersect(ray, (void*)env->shapes[p], &color, &nearest))
		{
			printf("intersection found\n");
			// If a hit is found compute the illumination
			// pixel[i][j] = object->color * light.brightness
			// return 1 (true)
		}
		else
		{
			// keep backround color (black, 0x00000000);
		}
		p++;
	}
	// my_pixel_put(img, i, j, color); // shader function for putting the color
	return (1);
}


void ft_render(t_img *img, t_env *env)
{
	int		i, j = 0;
	int		res_x, res_y = 10; // (width and height)
	printf("Entering rendering\n");
	// Iterate over all pixels
	while (i < res_y)
	{
		j = 0;
		while (j < res_x)
		{
			// First compute primary ray direction
			// ray = ft_build_ray(i, j);
			if (ft_tracer(i, j, env))
				printf("So far so good\n");
				// my_pixel_put(img, i, j, 0x00ffffff); // shader function for putting the color
			j++;
		}
		i++;
	}
}
