/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shadowing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:40:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/16 15:49:51 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint)
{
	t_ray	ray;

	ray.origin = *hitpoint;
	ray.direction = ft_normalize(vec_minus(light->coords, ray.origin));
	return (ray);
}

t_rgb	ft_shader(t_env *env, t_hit *hitp)
{
	t_list			*cursor;
	double			vect_len;
	t_light_solver	l;

	cursor = env->light;
	l.total_lights = env->amb_light.colors;
	while (cursor)
	{
		l.light = ((t_light *)(cursor->content));
		l.shadow_ray = ft_shadow_ray(l.light, &hitp->hitpoint);
		l.shadow_check.near = INFINITY;
		l.truelight = l.light->colors;
		vect_len = ft_vec_len(vec_minus(l.light->coords, hitp->hitpoint));
		if (!(ft_intersect(l.shadow_ray, env->shapes, &l.shadow_check) \
			&& l.shadow_check.near < vect_len))
		{
			l.intensity = ft_dot_product(l.shadow_ray.direction, hitp->normal);
			l.intensity = l.intensity * l.light->brightness;
			ft_color_multi(&l.truelight, l.intensity);
			l.total_lights = ft_colors_add(l.total_lights, l.truelight);
		}
		cursor = cursor->next;
	}
	return (ft_color_times_color(hitp->color, l.total_lights));
}
