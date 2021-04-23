/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shadowing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:40:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/23 16:36:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint)
{
	t_ray ray;
	
	ray.origin = *hitpoint;
	ray.direction = normalize(vec_minus(light->coords, ray.origin));
	return (ray);
}

t_rgb	ft_shading(t_env *env, t_impact_point *intersection, t_ray shadow_ray, t_light *light)
{
	t_rgb	ret_col;
	double	dot;
	t_rgb lite_cols;
	t_impact_point bool_struct;

	bool_struct.nearest = INFINITY;
	ret_col = color_times_color(intersection->color, env->amb_light.colors);
	if(ft_intersect(shadow_ray, env->shapes, &bool_struct) && bool_struct.nearest < vec_len(vec_minus(light->coords, intersection->hitpoint)))
		return (ret_col);
	else
	{
		lite_cols = light->colors;
		dot = dot_product(intersection->normal, shadow_ray.direction);
		if (dot < 0)
			dot = 0;
			
		color_multi(&lite_cols, (light->brightness * dot * 1));
		lite_cols = color_times_color(lite_cols, intersection->color);
		ret_col = colors_add(ret_col, lite_cols);
		color_check(&ret_col);
	}
	return(ret_col);
}