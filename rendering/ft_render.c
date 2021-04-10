/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/10 21:53:56 by rmeiboom      ########   odam.nl         */
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

t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint)
{
	t_ray ray;
	
	ray.origin = *hitpoint;
	ray.direction = normalize(vec_minus(light->coords, ray.origin));
	return (ray);
}

	

int		ft_intersect(t_ray ray, t_list *shape_list, t_impact_point *intersection, int shape)
{
	if (!shape_list)
		return (0);
	while (shape_list != NULL)
	{
		if (shape == SPHERE)
			ft_sphere_intersect((t_sphere*)shape_list->content, &ray, intersection);
		else if (shape == PLANE)
			ft_plane_intersect((t_plane*)shape_list->content, &ray, intersection);
		shape_list = shape_list->next;
	}
	if (intersection->nearest < INFINITY)
		return (1);
	return (0);
}

t_rgb	ft_calculate_color(t_env *env, t_impact_point *intersection, t_ray shadow_ray)
{
	t_rgb ret_col;
	float dot;
	float brightness = ((t_light*)env->light->content)->brightness;
	t_rgb light;
	
	light = ((t_light*)env->light->content)->colors;
	ret_col = color_times_color(intersection->color, env->amb_light.colors);
	
	dot = dot_product(intersection->normal, shadow_ray.direction);
	if (dot < 0)
		dot = 0;
		
	color_multi(&light, (brightness * dot));
	light = color_times_color(light, intersection->color);
	ret_col = colors_add(ret_col, light);
	color_check(&ret_col);
	
	return(ret_col);
}

int		ft_tracer(int x, int y, t_env *env, t_rgb *color)
{
	int i = 0;
	t_impact_point intersection;
	t_ray	primary_ray;
	t_ray	shadow_ray;
	// only when cam is on [0;0;Z]
	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
	intersection.nearest = INFINITY;
	
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y);
	while (i <= PLANE)
	{
		
		if(ft_intersect(primary_ray, (void*)env->shapes[i], &intersection, i))
		{
			intersection.hitpoint = calc_hitpoint(&primary_ray, intersection.nearest);
			shadow_ray = ft_shadow_ray((t_light*)env->light->content, &intersection.hitpoint);
			*color = ft_calculate_color(env, &intersection, shadow_ray);
		}
		i++;
	}
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
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
