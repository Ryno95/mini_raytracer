/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_vec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 12:55:47 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/13 13:04:17 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_structure.h"
#include <stdio.h>

t_coord	create_pos(double x, double y, double z)
{
	t_coord	new_pos;

	new_pos.x = x;
	new_pos.y = y;
	new_pos.z = z;
	return (new_pos);
}

t_vec	calc_hitpoint(t_ray *primary_ray, double t)
{
	t_vec	hit_p;

	hit_p.x = primary_ray->origin.x + primary_ray->direction.x * t;
	hit_p.y = primary_ray->origin.y + primary_ray->direction.y * t;
	hit_p.z = primary_ray->origin.z + primary_ray->direction.z * t;
	return (hit_p);
}

void	print_vec(t_vec vec, char *description)
{
	printf("%s.X: %f\n", description, vec.x);
	printf("%s.Y: %f\n", description, vec.y);
	printf("%s.Z: %f\n", description, vec.z);
}
