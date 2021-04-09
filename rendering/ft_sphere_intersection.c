/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/09 17:19:39 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_impact_point *intersection)
{
	float t =-1;
	float a; // always 1
	float b;
	float c;
	float discriminant;
	t_vec sub_ori_sph = vec_minus(ray->origin, sphere->coords);

	a = dot_product(ray->direction, ray->direction);
	b = 2 * (dot_product(ray->direction, sub_ori_sph));
	c = dot_product(sub_ori_sph, sub_ori_sph) - (sphere->diam * sphere->diam);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);

	if (b > 0)
		t = (-b + sqrt(discriminant)) / (a * 2);
	else if (b < 0)
		t = (-b - sqrt(discriminant)) / (a * 2);
	else
		t = -b / (a * 2);
	
	// printf("T: %f\nNearest: %f\n", t, intersection->nearest);
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