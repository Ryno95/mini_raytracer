/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/02 14:05:36 by rmeiboom      ########   odam.nl         */
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

void print_vec(t_vec vec)
{
	printf("VecX: %f\n", vec.x);
	printf("VecY: %f\n", vec.y);
	printf("VecZ: %f\n", vec.z);
}