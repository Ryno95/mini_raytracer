/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vec_products.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 20:36:36 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/16 16:02:01 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_structure.h"
#include <math.h>

double	ft_vec_len(t_vec vec)
{
	return (sqrt(pow((vec.x), 2) + pow((vec.y), 2) + pow((vec.z), 2)));
}

double	ft_dot_product(t_vec a, t_vec b)
{
	return ((a.x * b.x + a.y * b.y + a.z * b.z));
}

t_vec	ft_cross_product(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = ((a.x * b.z) - (a.z * b.x)) * -1;
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_vec	ft_normalize(t_vec vec)
{
	double	vl;

	vl = ft_vec_len(vec);
	vec.x /= vl;
	vec.y /= vl;
	vec.z /= vl;
	return (vec);
}
