/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/14 14:07:47 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ft_primary_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	t_vec dir = create_pos((float)x, (float)y, cam->cam_dist);
	
	ray.origin = cam->coords;
	ray.direction = normalize(vec_minus(dir, ray.origin));
	return (ray);
}

int		ft_intersect(t_ray ray, t_list **shape_list, t_impact_point *intersection)
{
	int i;
	t_list *tmp_lst;


	i = 0;
	if (!shape_list || !intersection)
		return (0);
	while (i <= PLANE)
	{
		tmp_lst = shape_list[i];
		while (tmp_lst != NULL)
		{
			if (i == SPHERE)
				ft_sphere_intersect((t_sphere*)tmp_lst->content, &ray, intersection);
			else if (i == PLANE)
				ft_plane_intersect((t_plane*)tmp_lst->content, &ray, intersection);
			tmp_lst = tmp_lst->next;
		}
		i++;
	}
	if (intersection->nearest < INFINITY)
		return (1);
	return (0);
}

int		ft_tracer(int x, int y, t_env *env, t_rgb *color)
{
	t_impact_point intersection;
	t_ray	primary_ray;
	t_ray	shadow_ray;
	// only when cam is on [0;0;Z]
	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
	intersection.nearest = INFINITY;
	
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y);
	if(ft_intersect(primary_ray, (void*)env->shapes, &intersection))
	{
		intersection.hitpoint = calc_hitpoint(&primary_ray, (intersection.nearest - 0.01));
		shadow_ray = ft_shadow_ray((t_light*)env->light->content, &intersection.hitpoint);
		*color = ft_shading(env, &intersection, shadow_ray);
	}
	return (0);
}

void ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	t_rgb color;

	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			color.r = 0;
			color.g = 0;
			color.b = 0;
			ft_tracer(j, i, env, &color);
			my_pixel_put(img, j, i, create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
}
