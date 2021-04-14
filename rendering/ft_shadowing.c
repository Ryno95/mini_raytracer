/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shadowing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:40:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/14 13:49:55 by rmeiboom      ########   odam.nl         */
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

t_rgb	ft_shading(t_env *env, t_impact_point *intersection, t_ray shadow_ray)
{
	t_rgb ret_col;
	float dot;
	float brightness = ((t_light*)env->light->content)->brightness;
	t_light *light_src = (t_light*)env->light->content;
	t_rgb light;
	t_impact_point bool_struct;
	
	// // iterate through list of objects to determine interobject shadows
	bool_struct.nearest = INFINITY;
	if(ft_intersect(shadow_ray, env->shapes, &bool_struct) && bool_struct.nearest < vec_len(vec_minus(light_src->coords, intersection->hitpoint)))
		ret_col = color_times_color(intersection->color, env->amb_light.colors);
	else
	{
		light = ((t_light*)env->light->content)->colors;
		ret_col = color_times_color(intersection->color, env->amb_light.colors);
		
		dot = dot_product(intersection->normal, shadow_ray.direction);
		if (dot < 0)
			dot = 0;
			
		color_multi(&light, (brightness * dot * 1));
		light = color_times_color(light, intersection->color);
		ret_col = colors_add(ret_col, light);
		color_check(&ret_col);
	}
	return(ret_col);
}