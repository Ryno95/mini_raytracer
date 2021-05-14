/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cylinder_intersect.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 10:25:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 17:14:37 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

static t_vec	ft_cyl_normal(t_vec hitp, t_vec center, t_vec ori)
{
	double	a;
	t_vec	normal;
	t_vec	center_hitp;
	t_vec	translate;

	center_hitp = vec_minus(hitp, center);
	a = dot_product(center_hitp, ori);
	translate = vec_add(center, vec_multiply(ori, a));
	normal = normalize(vec_minus(hitp, translate));
	return (normal);
}

static int	ft_in_range(t_cylinder *cy, double t, t_ray *ray)
{
	t_vec	hitp;
	double	a;
	double	b;
	double	c;

	hitp = calc_hitpoint(ray, t);
	a = vec_len(vec_minus(hitp, cy->center));
	c = cy->r;
	b = (a * a) - (c * c);
	b = sqrt(b);
	if (b < cy->height / 2 && b > cy->height / -2)
		return (1);
	return (0);
}

static double	ft_solve_quadratic(t_quadratic qua, t_cylinder *cy, t_ray *ray)
{
	double	t1;
	double	t2;

	qua.discrim = (qua.b * qua.b) - (4 * qua.a * qua.c);
	if (qua.discrim < 0)
		return (-1);
	t1 = (-qua.b + sqrt(qua.discrim)) / (2 * qua.a);
	t2 = (-qua.b - sqrt(qua.discrim)) / (2 * qua.a);
	if (t2 < t1 && t2 > 0 && ft_in_range(cy, t2, ray))
		t1 = t2;
	return (t1);
}

int	ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hitp)
{
	t_quadratic	q;
	t_vec		dir_x_norm;
	t_vec		vec_x_norm;

	dir_x_norm = cross_product(ray->direction, cy->ori);
	vec_x_norm = cross_product(vec_minus(ray->origin, cy->center), cy->ori);
	q.a = dot_product(dir_x_norm, dir_x_norm);
	q.b = 2 * dot_product(dir_x_norm, vec_x_norm);
	q.c = dot_product(vec_x_norm, vec_x_norm) - (cy->r * cy->r);
	q.t1 = ft_solve_quadratic(q, cy, ray);
	if (q.t1 < hitp->near && q.t1 >= 0 && ft_in_range(cy, q.t1, ray))
	{
		ass_hitpoint(q.t1, cy->colors, cy->id, hitp);
		hitp->hitpoint = calc_hitpoint(ray, q.t1);
		hitp->normal = ft_cyl_normal(hitp->hitpoint, cy->center, cy->ori);
		return (1);
	}
	return (0);
}
