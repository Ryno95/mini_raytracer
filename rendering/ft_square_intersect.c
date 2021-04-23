/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_square_intersect.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 10:44:42 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/23 16:36:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		ft_is_inside_square(t_square *sq, t_vec hitp)
{
	t_vec dist;
	double border;

	dist = vec_minus(hitp, sq->coords);
	border = sq->side_size * 0.5;
	if (fabs(dist.x) <= border && fabs(dist.y) <= border && fabs(dist.z) <= border)
		return (1);
	return (0);
}

int		ft_square_intersect(t_square *sq, t_ray *ray, t_impact_point *intersect)
{
	double denominator = dot_product(sq->vect_coords, ray->direction);
	// if (denominator <= 0.00001)
	// 	return (0);
		
	t_vec diff = vec_minus(sq->coords ,ray->origin);
	double t = dot_product(diff, sq->vect_coords) / denominator;
	t_vec hitp = calc_hitpoint(ray, t);

	if (t < intersect->nearest && t >= 0 && ft_is_inside_square(sq, hitp))
	{
		ass_hitpoint(t, sq->colors, sq->id, intersect);
		intersect->normal = sq->vect_coords;
		if (denominator > 0)
			intersect->normal = vec_multiply(sq->vect_coords, -1);
		return (1);
	}
	return (0);
}