/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 18:20:04 by rmeiboom      ########   odam.nl         */
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
	quad.b = 2 * (dot_product(ray->direction, ori_cen));
	quad.c = dot_product(ori_cen, ori_cen) - (sphere->diam * sphere->diam);
	quad.discrim = quad.b * quad.b - 4 * quad.c;
	if (quad.discrim < 0)
		return (0);
	t = ft_solve_circle(quad);
	if (t >= 0 && t < hitp->near)
	{
		ass_hitpoint(t, sphere->colors, sphere->id, hitp);
		hitp->hitpoint = calc_hitpoint(ray, t);
		hitp->normal = normalize(vec_minus(hitp->hitpoint, sphere->center));
		return (1);
	}
	return (0);
}
