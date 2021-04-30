/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 11:14:39 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 17:43:01 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	ft_print_color(t_rgb vector)
{
	printf("Color: %f %f %f\n", vector.r, vector.g, vector.b);
}

void	ft_print_vect(t_vec vector, char *pre)
{
	printf("%s: %lf %lf %lf\n", pre, vector.x, vector.y, vector.z);
}

// int    ft_debugray(int keycode, int x, int y, t_env *env)
// {
// 	// t_ray 			*ray;
// 	// t_hit 			*impact;
// 	// t_rgb			color;
// 	// t_ray			shadow_ray;
// 	// t_camera		*camera = ((t_camera*)(env->cam_list->content));
	
// 	// x = x - env->res.x / 2;
// 	// y = env->res.y / 2 - y;
// 	// env->debug = 1;
// 	// impact = (t_hit *)ft_calloc(sizeof(t_hit), 1);
// 	// impact->nearest = INFINITY;
// 	// ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	
	
// 	// *ray = ft_primary_ray(camera, x, y, camera->cam_dist * 2);
// 	// ft_intersect(*ray, env->shapes, impact);
	
	
// 	// // shadow_ray = ft_shadow_ray((t_light*)env->light->content, &impact->hitpoint);
// 	// // color = ft_shading(env, &impact, shadow_ray);

// 	// printf("T: %lf\n", impact->nearest);
// 	// impact->hitpoint = calc_hitpoint(ray, impact->nearest);
// 	// ft_print_vect(impact->hitpoint, "Hitpoint");
// 	// ft_print_vect(impact->normal, "Normal");
// 	// // ft_print_color(color);

// 	// printf("\n\n");
// 	// free(impact);
// 	// free(ray);
// 	// env->debug = 0;
// 	return (0);
// }
