/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/31 17:51:58 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	vec_len(t_vec vec)
{
	return(sqrt(pow((vec.x), 2) + pow((vec.y), 2) + pow((vec.z), 2)));	
}

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

t_vec	vec_multiply(t_vec a, float factor)
{
	a.x *= factor;
	a.y *= factor;
	a.z *= factor;

	return (a);
}

t_vec	vec_divide(t_vec a, float factor)
{
	a.x /= factor;
	a.y /= factor;
	a.z /= factor;

	return (a);
}