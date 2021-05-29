/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_triangle_intersection.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 17:22:28 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/29 10:48:47 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

static int	ft_is_inside_tri(t_triangle *tri, t_vec hitp, t_vec normal)
{
	t_vec	side;
	t_vec	cross;

	side = vec_minus(tri->scnd_pnt, tri->frst_pnt);
	cross = ft_cross_product(side, vec_minus(hitp, tri->frst_pnt));
	if (ft_dot_product(normal, cross) < 0)
		return (0);
	side = vec_minus(tri->frst_pnt, tri->thrd_pnt);
	cross = ft_cross_product(side, vec_minus(hitp, tri->thrd_pnt));
	if (ft_dot_product(normal, cross) < 0)
		return (0);
	side = vec_minus(tri->thrd_pnt, tri->scnd_pnt);
	cross = ft_cross_product(side, vec_minus(hitp, tri->scnd_pnt));
	if (ft_dot_product(normal, cross) < 0)
		return (0);
	return (1);
}

double	ft_triangle_intersect(t_triangle *tri, t_ray *ray, t_hit *hitp)
{
	double	t;
	t_vec	sides[2];
	t_vec	normal;
	double	angle;
	t_vec	point;

	sides[0] = vec_minus(tri->scnd_pnt, tri->frst_pnt);
	sides[1] = vec_minus(tri->thrd_pnt, tri->frst_pnt);
	normal = ft_normalize(ft_cross_product(sides[0], sides[1]));
	angle = ft_dot_product(normal, ray->direction);
	if (fabs(angle) < 0.00001)
		return (0);
	t = ft_dot_product(normal, vec_minus(tri->frst_pnt, ray->origin)) / angle;
	point = calc_hitpoint(ray, t);
	if (t >= 0 && t < hitp->near && ft_is_inside_tri(tri, point, normal))
	{
		ass_hitpoint(t, tri->colors, tri->id, hitp);
		hitp->normal = normal;
		if (ft_dot_product(normal, ray->direction) > 0)
			hitp->normal = vec_multiply(normal, -1);
		return (1);
	}		
	return (0);
}
