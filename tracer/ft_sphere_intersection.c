/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/02 17:18:17 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, float *nearest, unsigned int *col)
{
	float t = 1e-5;
	float a; // always 1
	float b;
	float c;
	float discriminant;

	a = dot_product(ray->direction, ray->direction);
	b = 2 * (dot_product(ray->direction, vec_minus(ray->origin, sphere->coords)));
	c = dot_product(vec_minus(ray->origin, sphere->coords), vec_minus(ray->origin, sphere->coords)) - (sphere->diam * sphere->diam);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);

	if (b > 0)
		t = (-b + sqrt(discriminant)) / (a * 2);
	else if (b < 0)
		t = (-b - sqrt(discriminant)) / (a * 2);
	else
		t = -b / (a * 2);
	
	if (t >= 0 && t < *nearest)
	{
		*nearest = t;
		*col = sphere->colors.rgb;
		return (1);
	}
	return (0);
}