/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 17:28:15 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

static double	ft_solve_circle(t_quadratic quad)
{
	double	t1;
	double	t2;

	t1 = (-quad.b + sqrt(quad.discrim)) / 2;
	t2 = (-quad.b - sqrt(quad.discrim)) / 2;
	if (t2 >= 0 && t2 < t1)
		t1 = t2;
	return (t1);
}

double	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_hit *hitp)
{
	t_quadratic	quad;
	double		t;
	t_vec		ori_cen;

	ori_cen = vec_minus(ray->origin, sphere->center);
	quad.b = 2 * (ft_dot_product(ray->direction, ori_cen));
	quad.c = ft_dot_product(ori_cen, ori_cen) - (sphere->diam * sphere->diam);
	quad.discrim = quad.b * quad.b - 4 * quad.c;
	if (quad.discrim < 0)
		return (0);
	t = ft_solve_circle(quad);
	if (t >= 0 && t < hitp->near)
	{
		ass_hitpoint(t, sphere->colors, sphere->id, hitp);
		hitp->hitpoint = calc_hitpoint(ray, t);
		hitp->normal = ft_normalize(vec_minus(hitp->hitpoint, sphere->center));
		if (ft_dot_product(hitp->normal, ray->direction) > 0)
			hitp->normal = vec_multiply(hitp->normal, -1);
		return (1);
	}
	return (0);
}
