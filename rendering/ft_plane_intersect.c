/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:29:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/10 21:53:45 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_plane_intersect(t_plane *plane, t_ray *ray, t_impact_point *intersection)
{
	float denominator = dot_product(plane->vect_coords, ray->direction);
	t_vec diff = vec_minus(plane->coords ,ray->origin);
	float t = dot_product(diff, plane->vect_coords) / denominator;
	
	if (t < intersection->nearest && t >= 0)
	{
		intersection->nearest = t;
		intersection->color = plane->colors;
		intersection->object_id = plane->id;
		return (1);
	}
	return (1);
}