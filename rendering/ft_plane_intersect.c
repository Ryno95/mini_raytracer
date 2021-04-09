/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:29:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/09 16:42:19 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_plane_intersect(t_plane *plane, t_ray *ray, t_impact_point *intersection)
{
	// float a = dot_product(vec_minus(ray->origin, plane->coords), plane->vect_coords);
	// float b = dot_product(ray->direction, plane->vect_coords);
	// float t;


	// t = -a / b;
	// if (t < *nearest && t >= 0)
	float denominator = dot_product(plane->vect_coords, ray->direction);
	t_vec diff = vec_minus(plane->coords ,ray->origin);
	float t = dot_product(diff, plane->vect_coords) / denominator;
	
	// if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
	// 	return (-1);
	
	// printf("T:%f\n", t);
	// if (t >= 0 && t < *nearest)
	if (t < intersection->nearest && t >= 0)
	{
		intersection->nearest = t;
		intersection->color = plane->colors;
		intersection->object_id = plane->id;
		// printf("hitobject: %p\n", hit_object);
		return (1);
	}
	return (1);
}

// identifier: pl
// x,y,z coordinates: 0.0,0.0,-10.0
// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// R,G,B colors in range [0-255]: 0, 0, 255