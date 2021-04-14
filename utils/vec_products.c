/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_products.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 20:36:36 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/14 12:32:59 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// range for nroma vects[-1;1]
float	dot_product(t_vec a, t_vec b)
{
	return ((a.x*b.x + a.y*b.y + a.z*b.z));
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = -((a.x * b.z) - (a.z * b.x));
	c.z = (a.x * b.y) - (a.y * b.x);

	return (c);
}

t_coord create_pos(float x, float y, float z)
{
	t_coord new_pos;

	new_pos.x = x;
	new_pos.y = y;
	new_pos.z = z;

	return (new_pos);
}

t_vec normalize(t_vec vec)
{
	float vl = vec_len(vec);

	vec.x /= vl;
	vec.y /= vl;
	vec.z /= vl;

	return (vec);
}

t_vec calc_hitpoint(t_ray *primary_ray, float t)
{
	t_vec hit_p;
	
	// printf("t: %f\n", t);
	// print_vec(primary_ray->origin, "ray->ori");
	// print_vec(primary_ray->direction, "ray->dir");
	hit_p.x = primary_ray->origin.x + primary_ray->direction.x * t;
	hit_p.y = primary_ray->origin.y + primary_ray->direction.y * t;
	hit_p.z = primary_ray->origin.z + primary_ray->direction.z * t;
	// print_vec(hit_p, "HitP");

	return (hit_p);
}

// t: 149.302887

// ray->ori.X:  0.000000
// ray->dir.X:  0.002960
// HitP.X: 		0.442003

// ray->ori.Y:  0.000000
// ray->dir.Y:  -0.079932
// HitP.Y: 		-11.934093

// ray->ori.Z:  -125.000000
// ray->dir.Z:  0.996796
// HitP.Z: 		23.824509