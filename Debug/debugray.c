/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 11:14:39 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/21 15:54:30 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ft_print_vect(t_vec vector, char *pre)
{
	printf("%s: %lf %lf %lf\n", pre, vector.x, vector.y, vector.z);
}

int    ft_debugray(int keycode, int x, int y, t_env *env)
{
	t_ray 			ray;
	t_impact_point 	impact;
	t_rgb			color;
	t_ray			shadow_ray;
	t_camera		*camera = ((t_camera*)(env->cam_list->content));
	t_list			*lst;
	
	env->debug = 1;
	// impact = (t_impact_point *)ft_calloc(sizeof(t_impact_point), 1);
	impact.nearest = INFINITY;
	// ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	// printf("x:%d\ny:%d\n", x, y);
	// printf();
	ray = ft_primary_ray(camera, x, y);
	ft_intersect(ray, env->shapes, &impact);
	ft_print_color(impact.color);
	lst = env->light;
	impact.hitpoint = calc_hitpoint(&ray, impact.nearest);
	while (lst)
	{
		shadow_ray = ft_shadow_ray((t_light*)lst->content, &impact.hitpoint);
		color = ft_shading(env, &impact, shadow_ray, (t_light*)lst->content);
		lst = lst->next	;
	}

	printf("T: %lf\n", impact.nearest);
	ft_print_vect(impact.hitpoint, "Hitpoint");
	ft_print_vect(impact.normal, "Normal");
	ft_print_color(color);

	printf("\n\n");
	// free(impact);
	// free(ray);
	env->debug = 0;
	return (0);
}
