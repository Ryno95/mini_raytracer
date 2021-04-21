/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:29:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/21 20:08:47 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_plane_intersect(t_plane *plane, t_ray *ray, t_impact_point *intersection)
{
	double denominator = dot_product(plane->vect_coords, ray->direction);
	t_vec diff = vec_minus(plane->coords ,ray->origin);
	double t = dot_product(diff, plane->vect_coords) / denominator;
	
	if (t < intersection->nearest && t > 0)
	{
		// printf("PLANE FOUND t: %lf\n", t);
		intersection->nearest = t;
		intersection->color = plane->colors;
		intersection->object_id = plane->id;
		if (dot_product(plane->vect_coords, ray->direction) > 0)
			intersection->normal = vec_multiply(plane->vect_coords, -1);
		else
			intersection->normal = plane->vect_coords;
		return (1);
	}
	return (0);
}