/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/02 19:50:34 by rmeiboom      ########   odam.nl         */
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

int		ft_intersect(t_ray ray, t_list *shape_list, unsigned int *col, float *nearest)
{
	t_vec point;
	int i;
	// int j = 1;
	void *ptr;
	// my_lstiter(shape_list, &ray, nearest, (void*)ft_sphere_intersect);
	
	if (!shape_list)
		return (-1);
	i = -1;
	// ptr = shape_list;
	while (shape_list != NULL)
	{
		// ((t_sphere*)(env.shapes[SPHERE]->content))
		if(ft_sphere_intersect((t_sphere*)shape_list->content, &ray, nearest, col));
			i = 1;
		// printf("address: %p\n", shape_list);
		shape_list = shape_list->next;
		
		// printf("X:%f\n", ((t_sphere*)(shape_list->content))->coords.x);
		// printf("TEST: %d\n", j);
		// j++;
	}
	// shape_list = ptr;
	// if (ft_sphere_intersect((t_sphere*)(shape_list), &ray, nearest) > 0)
	// {
	// 	point = vec_add(ray.origin, vec_multiply(ray.direction, *nearest));
		
	// 	return (1);
	// }
		
	return (i);
}

int		ft_tracer(int x, int y, t_env *env, unsigned int *color)
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
	while (i <= SPHERE)
	{
		ft_intersect(ray, (void*)env->shapes[i], color, &nearest);
		i++;
	}
	return (0);
}


void ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	unsigned int color;

	// Iterate over all pixels
	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			color = 0x0f000000;
			ft_tracer(j, i, env, &color);
			my_pixel_put(img, j, i, color); // shader function for putting the color
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