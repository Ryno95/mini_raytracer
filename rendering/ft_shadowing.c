/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shadowing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:40:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 18:07:03 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint)
{
	t_ray ray;
	
	ray.origin = *hitpoint;
	ray.direction = normalize(vec_minus(light->coords, ray.origin));
	return (ray);
}

t_rgb	ft_shader(t_env *env, t_hit *hitp)
{
	t_list *cursor = env->light;
	t_light *light;
	t_hit	shadow_check;
	t_ray	shadow_ray;
	t_rgb	total_lights;
	float intensity;
	t_rgb truelight;

	total_lights = env->amb_light.colors;
	while (cursor)
	{
		light = ((t_light*)(cursor->content));
		shadow_ray = ft_shadow_ray(light, &hitp->hitpoint);
		shadow_check.near = INFINITY;
		truelight = light->colors;
		if(!(ft_intersect(shadow_ray, env->shapes, &shadow_check) && shadow_check.near < vec_len(vec_minus(light->coords, hitp->hitpoint))))
		{
			intensity = dot_product(shadow_ray.direction, hitp->normal);
			intensity = intensity * light->brightness;
			ft_color_multi(&truelight, intensity);
			total_lights = ft_colors_add(total_lights, truelight);
		}
		cursor = cursor->next;
	}
	return (ft_color_times_color(hitp->color, total_lights));
}