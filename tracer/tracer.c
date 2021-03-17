/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/16 21:30:01 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Psuedo code for a raytracing algorithm


// what is the relationship of the camera to the  raster
// define ypsilon 1e-6

t_ray	ft_build_ray(int x, int j)
{
	t_ray ray;
	// tan a = opposite_side / ajacent_side
	// 

	return (ray);
}

int	ft_tracer(int x, int y, t_env *env)
{
	int p = 0;
	int r = 0;
	float nearest = INFINITY;
	unsigned int color = 0;
	t_ray	ray;
	// First compute primary ray direction
	ray = ft_build_ray(x, y);
	while (p < TRIANGLE)
	{
		// while (r < env->shapes[p] ) // add number of triangels??????
		// // maybe necesary to add another loop for the mount of triangles in the object
	
		// Shoot primary ray in the scene in search for an intersection
		// in my intersect, iterate over all shapes
		// my_lstiter(env->shapes[i], img, (void*)ft_draw_square);
		// also triangle intersect for each triangel in the shape
		if(ft_intersect(ray, env->shapes[p]))
		{
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
	
	return (-11);
}


void ft_raster(t_img *img, t_env *env)
{
	int		i,j,k = 0;
	int		res_x, res_y = 0; // (width and height)
	
	// Iterate over all pixels
	while (i < env->res.y)
	{
		while (j < env->res.x)
		{
			// First compute primary ray direction
			// ray = ft_build_ray(i, j);
			if (ft_tracer(i, j, env))
				my_pixel_put(img, i, j, 0x00ffffff); // shader function for putting the color
			j++;
		}
		i++;
	}
}
