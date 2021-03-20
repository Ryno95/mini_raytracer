/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_products.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 20:36:36 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/18 21:55:17 by rmeiboom      ########   odam.nl         */
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