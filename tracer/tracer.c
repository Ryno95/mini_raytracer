/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/01 22:12:46 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ft_build_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	// printf("entering ray builder\n");
	ray.origin = cam->vect_coords;
	// printf("cam_coords\nX:%f\nY:%f\nZ:%f\n", cam->coords.x, cam->coords.y, cam->coords.z);

	ray.direction = vec_minus(create_pos((float)x, (float)y, cam->cam_dist), ray.origin);
	normalize(&ray.direction);
	// printf("Ray dir:\n x:%f\n y:%f\n z:%f\n", ray.direction.x, ray.direction.y, ray.direction.z);

	return (ray);
}

int		ft_intersect(t_ray ray, void *shape_list, unsigned int *col, float *nearest)
{
	if (ft_sphere_intersect((t_sphere*)(shape_list), &ray))
		return (1);
		
	return (-1);
}

int		ft_tracer(int x, int y, t_env *env)
{
	int p = SPHERE;
	float nearest = INFINITY;
	unsigned int color = 0;
	t_ray	ray;
	
	// only when cam is on [0;0;Z]
	x -= env->res.x / 2;
	y = (env->res.y / 2) - y;
	// x = (2 *((x + 0.5) / env->res.x) - 1) * tan(((t_camera*)(env->cam_list->content))->fov / 2 * M_PI / 180 ) * (env->res.x / env->res.y);
	// y = 1 - (2 * ((y + 0.5) / env->res.y) * tan(((t_camera*)(env->cam_list->content))->fov / 2 * M_PI / 180 ));
	// x = x - env->res.x / 2;
	// y = env->res.y / 2 - y;
	// printf()
	// First compute primary ray direction
	ray = ft_build_ray((t_camera*)(env->cam_list->content), x, y);
	// printf("Entering tracer\n");
	if (ft_intersect(ray, (void*)env->shapes[SPHERE]->content, &color, &nearest) == 1)
	{
		// printf("INTERSECTION FOUND\n");
		return (1);
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
	return (0);
}


void ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	unsigned int col;

	// Iterate over all pixels
	i = 0;
	col = 0x0F000000;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			if (ft_tracer(i, j, env) == 1)
			{
				// printf("So far so good:\ni: %d\nj: %d\n", i ,j);
				col = ((t_sphere*)(env->shapes[SPHERE]->content))->colors.rgb;
				// printf("COL: %u\n", col);
			}
			my_pixel_put(img, i, j, col); // shader function for putting the color
			j++;
		}
		i++;
	}
}
