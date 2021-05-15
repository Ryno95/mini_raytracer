/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_square_intersect.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 10:44:42 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 13:41:06 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

static int	ft_is_inside_square(t_square *sq, t_vec hitp)
{
	t_vec	d;
	double	border;

	d = vec_minus(hitp, sq->center);
	border = sq->side_size * 0.5;
	if (fabs(d.x) <= border && fabs(d.y) <= border && fabs(d.z) <= border)
		return (1);
	return (0);
}

int	ft_square_intersect(t_square *sq, t_ray *ray, t_hit *hitp)
{
	double	denominator;
	t_vec	diff;
	double	t;
	t_vec	hitp_coords;

	denominator = ft_dot_product(sq->orient, ray->direction);
	if (denominator <= 0.00001)
		return (0);
	diff = vec_minus(sq->center, ray->origin);
	t = ft_dot_product(diff, sq->orient) / denominator;
	hitp_coords = calc_hitpoint(ray, t);
	if (t < hitp->near && t >= 0 && ft_is_inside_square(sq, hitp_coords))
	{
		ass_hitpoint(t, sq->colors, sq->id, hitp);
		hitp->normal = sq->orient;
		if (denominator > 0)
			hitp->normal = vec_multiply(sq->orient, -1);
		return (1);
	}
	return (0);
}
