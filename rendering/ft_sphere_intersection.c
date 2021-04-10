/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/10 21:55:28 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_impact_point *intersection)
{
	float t = -1;
	float b;
	float c;
	float discriminant;
	t_vec sub_ori_sph = vec_minus(ray->origin, sphere->coords);

	b = 2 * (dot_product(ray->direction, sub_ori_sph));
	c = dot_product(sub_ori_sph, sub_ori_sph) - (sphere->diam * sphere->diam);
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (0);
	if (b > 0)
		t = (-b + sqrt(discriminant)) / 2;
	else if (b < 0)
		t = (-b - sqrt(discriminant)) / 2;
	else
		t = -b / 2;

	if (t >= 0 && t < intersection->nearest)
	{
		intersection->nearest = t;
		intersection->color = sphere->colors;
		intersection->object_id = sphere->id;
		intersection->hitpoint = calc_hitpoint(ray, t);
		intersection->normal = normalize(vec_minus(intersection->hitpoint, sphere->coords));
		return (1);
	}
	return (0);
}