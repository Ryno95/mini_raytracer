/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shadowing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:40:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/24 17:58:13 by rmeiboom      ########   odam.nl         */
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

t_rgb	ft_shader(t_env *env, t_hit *hitp)
{
	// true light col = objcol * amblight_col;
	t_list *cursor = env->light;
	t_light *light;
	t_hit	shadow_check;
	t_ray	shadow_ray;
	t_rgb	total_lights;
	float intensity;
	t_rgb truelight;

	// for each light
	
	total_lights = env->amb_light.colors;
	while (cursor)
	{
		light = ((t_light*)(cursor->content));
		shadow_ray = ft_shadow_ray(light, &hitp->hitpoint);
		shadow_check.nearest = INFINITY;
		truelight = light->colors;
		// if !intersect
		if(!(ft_intersect(shadow_ray, env->shapes, &shadow_check) && shadow_check.nearest < vec_len(vec_minus(light->coords, hitp->hitpoint))))
		{
			// add lights
			intensity = dot_product(shadow_ray.direction, hitp->normal);
			intensity = intensity * light->brightness;
			color_multi(&truelight, intensity);
			total_lights = colors_add(total_lights, truelight);
		}
		cursor = cursor->next;
	}
	return (color_times_color(hitp->color, total_lights));
}