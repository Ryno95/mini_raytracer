/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/06 22:01:30 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ft_build_ray(t_camera *cam, int x, int y)
{
	t_ray ray;

	ray.origin = cam->coords;
	ray.direction = vec_minus(create_pos((float)x, (float)y, cam->cam_dist), ray.origin);
	normalize(&ray.direction);
	return (ray);
}

int		ft_intersect(t_ray ray, t_list *shape_list, t_rgb *col, float *nearest, int shape)
{
	t_vec point;
	// my_lstiter(shape_list, &ray, nearest, (void*)ft_sphere_intersect);
	
	if (!shape_list)
		return (-1);
	while (shape_list != NULL)
	{
		if (shape == SPHERE)
			ft_sphere_intersect((t_sphere*)shape_list->content, &ray, nearest, col);
		else if (shape == PLANE)
			ft_plane_intersect((t_plane*)shape_list->content, &ray, nearest, col);
		shape_list = shape_list->next;
	}
		
	if (*nearest < INFINITY)
		return (1);
	return (0);
}

int		ft_tracer(int x, int y, t_env *env, t_rgb *color)
{
	int i = 0;
	float nearest = INFINITY;
	void *ptr;
	t_ray	ray;
	
	// only when cam is on [0;0;Z]
	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
	
	// First compute primary ray direction
	ray = ft_build_ray((t_camera*)(env->cam_list->content), x, y);
	// printf("Entering tracer\n");
	while (i <= PLANE)
	{
		if(ft_intersect(ray, (void*)env->shapes[i], color, &nearest, i));
			color_multi(color, env->amb_light.ratio);
		// *color = co
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