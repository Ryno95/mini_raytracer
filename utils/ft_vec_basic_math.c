/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vec_basic_math.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/16 16:01:16 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_structure.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec	vec_minus(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec	vec_multiply(t_vec a, double factor)
{
	a.x *= factor;
	a.y *= factor;
	a.z *= factor;
	return (a);
}

t_vec	vec_divide(t_vec a, double factor)
{
	a.x /= factor;
	a.y /= factor;
	a.z /= factor;
	return (a);
}

t_vec	vec_by_vec(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}
