/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:29:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/16 23:14:07 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

double	ft_plane_intersect(t_plane *plane, t_ray *ray, t_hit *hitp)
{
	double	denominator;
	t_vec	diff;
	double	t;

	denominator = ft_dot_product(plane->orient, ray->direction);
	diff = vec_minus(plane->coords, ray->origin);
	t = ft_dot_product(diff, plane->orient) / denominator;
	if (t < hitp->near && t >= 0)
	{
		ass_hitpoint(t, plane->colors, plane->id, hitp);
		hitp->normal = plane->orient;
		if (denominator > 0)
			hitp->normal = vec_multiply(plane->orient, -1);
		return (1);
	}
	return (0);
}
