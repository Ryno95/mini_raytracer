/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_products.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 20:36:36 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 17:43:01 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

double	dot_product(t_vec a, t_vec b)
{
	return ((a.x * b.x + a.y * b.y + a.z * b.z));
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = ((a.x * b.z) - (a.z * b.x)) * -1;
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_coord	create_pos(double x, double y, double z)
{
	t_coord	new_pos;

	new_pos.x = x;
	new_pos.y = y;
	new_pos.z = z;
	return (new_pos);
}

t_vec	normalize(t_vec vec)
{
	double	vl;

	vl = vec_len(vec);
	vec.x /= vl;
	vec.y /= vl;
	vec.z /= vl;
	return (vec);
}

t_vec	calc_hitpoint(t_ray *primary_ray, double t)
{
	t_vec	hit_p;

	hit_p.x = primary_ray->origin.x + primary_ray->direction.x * t;
	hit_p.y = primary_ray->origin.y + primary_ray->direction.y * t;
	hit_p.z = primary_ray->origin.z + primary_ray->direction.z * t;
	return (hit_p);
}
