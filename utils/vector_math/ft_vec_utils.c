/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vec_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 18:00:17 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

double	vec_len(t_vec vec)
{
	return (sqrt(pow((vec.x), 2) + pow((vec.y), 2) + pow((vec.z), 2)));
}

t_vec	ft_vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec	ft_vec_sub(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec	ft_vec_multi(t_vec a, double factor)
{
	a.x *= factor;
	a.y *= factor;
	a.z *= factor;
	return (a);
}

t_vec	ft_vec_divide(t_vec a, double factor)
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
