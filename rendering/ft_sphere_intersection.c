/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/23 16:36:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_impact_point *intersection)
{
	double t = -1;
	double b;
	double c;
	double discriminant;
	t_vec ori_cen = vec_minus(ray->origin, sphere->coords);
	// printf("entering sphere intersect\n");

	b = 2 * (dot_product(ray->direction, ori_cen));
	c = dot_product(ori_cen, ori_cen) - (sphere->diam * sphere->diam);
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
		// printf("SPHEREfound t: %f\n", t);
		// ass_hitpoint(t, sphere->colors, sphere->id, intersection);
		intersection->nearest = t;
		intersection->color = sphere->colors;
		intersection->object_id = sphere->id;
		intersection->hitpoint = calc_hitpoint(ray, t);
		intersection->normal = normalize(vec_minus(intersection->hitpoint, sphere->coords));
		return (1);
	}
	return (0);
}