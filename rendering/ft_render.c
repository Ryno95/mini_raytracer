/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/09 18:26:23 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// MAKE A CHECK COLOR RANGE FUNCTION

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
	// print_vec(light->coords, "light");
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
	int i = 0;
	float t = INFINITY;
	t_rgb obj_col;
	t_rgb light_cols = ((t_light*)(env->light->content))->colors;
	// int red = ((t_light*)env->light->content)->colors.r;
	// t_rgb light_color;/
	float dot;
	obj_col.t = 0;
		
	obj_col = intersection->color;
	color_multi(&obj_col, env->amb_light.ratio);
	// sphere_intersect_norm = normalize(sphere_hitpoint - sphere_center);
	// light_direction = shadow_ray.dir;
	dot = dot_product(intersection->normal, shadow_ray.direction);
	// printf("dot: %f\n", dot);
	if (dot < 0)
		dot = 0;
	color_multi(&light_cols, dot);
	// printf("light COL: %d\n", light_cols.r);
	obj_col = color_times_color(obj_col, light_cols);
	color_check(&obj_col);
	return (obj_col);

	// while (i <= PLANE)
	// {
	// 	if(ft_intersect(shadow_ray, (void*)env->shapes[i], &color, &t, i)); // or intersection pooint is bigger than 3
	// 	{
	// 		color_multi(&col, 0);
	// 		break;	
	// 	}
	// 	i++;
	// }
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
	
	// First compute primary ray direction
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y);
	// printf("Entering tracer\n");
	while (i <= PLANE)
	{
		
		if(ft_intersect(primary_ray, (void*)env->shapes[i], &intersection, i))
		{
			intersection.hitpoint = calc_hitpoint(&primary_ray, intersection.nearest);
			shadow_ray = ft_shadow_ray((t_light*)env->light->content, &intersection.hitpoint);
			// *color = intersection.color;
			*color = ft_calculate_color(env, &intersection, shadow_ray);
			
			// *color = ft_calculate_color(env, &intersection, shadow_ray);
			// color_multi(color, env->amb_light.ratio);
			// printf("hit_obj:%d\n", *(int*)hit_obj);
		}
		i++;
	}
	return (0);
}


void ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	t_rgb color;

	// Iterate over all pixels
	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			color.rgb = 0x0f000000;
			ft_tracer(j, i, env, &color);
			my_pixel_put(img, j, i, color.rgb); // shader function for putting the color
			// printf("color:%u\n", color);
			j++;
		}
		i++;
	}
}

	// while (p < TRIANGLE)
	// {
	
	// 	// Shoot primary ray in the scene in search for an intersection
	// 	// in my intersect, iterate over all shapes
	// 	// my_lstiter(env->shapes[i], img, (void*)ft_draw_square);
	// 	if(ft_intersect(ray, (void*)env->shapes[p], &color, &nearest) != -1)
	// 	{
	// 		printf("intersection found\n");
	// 		// If a hit is found compute the illumination
	// 		// pixel[i][j] = object->color * light.brightness
	// 		// return 1 (true)
	// 	}
	// 	else
	// 	{
	// 		// keep backround color (black, 0x00000000);
	// 	}
	// 	p++;
	// }
	// my_pixel_put(img, i, j, color); // shader function for putting the color