/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 17:36:00 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>
#include <stdio.h>

double	vec_len(t_vec vec)
{
	return (sqrt(pow((vec.x), 2) + pow((vec.y), 2) + pow((vec.z), 2)));
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

void	print_vec(t_vec vec, char *description)
{
	printf("%s.X: %f\n", description, vec.x);
	printf("%s.Y: %f\n", description, vec.y);
	printf("%s.Z: %f\n", description, vec.z);
}

t_vec vec_by_vec(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}