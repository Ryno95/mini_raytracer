/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_products.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 20:36:36 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/31 17:09:29 by rmeiboom      ########   odam.nl         */
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

void normalize(t_vec *vec)
{
	float vl = vec_len(*vec);

	vec->x /= vl;
	vec->y /= vl;
	vec->z /= vl;
}
