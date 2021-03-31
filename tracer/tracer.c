/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/31 18:23:32 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ft_build_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	// printf("entering ray builder\n");
	ray.origin = cam->vect_coords;
	// printf("cam_coords\nX:%f\nY:%f\nZ:%f\n", cam->coords.x, cam->coords.y, cam->coords.z);

	ray.direction = vec_minus(create_pos((float)x, (float)y, 1.0), ray.origin);
	normalize(&ray.direction);
	// printf("Ray dir:\n x:%f\n y:%f\n z:%f\n", ray.direction.x, ray.direction.y, ray.direction.z);

	return (ray);
}

int		ft_intersect(t_ray ray, void *shape_list, unsigned int *col, float *nearest)
{
	ft_sphere((t_sphere*)(shape_list), &ray);
	// I think i want to calculate t in P = orig + t * dir
	// if(intersect() && t > 0)
	// To calculate a point on the ray you need:
	// The ray origin(from camera) (O), ray direction (from args) (R) , and a point (P) along the ray [x, y]
	// ray in parametric form:
	// P = O + tR  (t = distance from origin to the point, Az - Bz?)
	// For the parametric I = R(t) = (1 - t)C +tP
	// Where:  I = Intersection
			// t = weighted average (check formula)
		   	// C = camera coords
		   	// P = Pixel, in pixelgrid coords
	// You have C[x,y,z] and P[x,y, z(with the tangient of FOV)]
	// t needs to be calculated for each point encountered ex.
			// Ix = Rx(t) = (1 - t)Cx + tPx
			// Iy = Ry(t) = (1 - t)Cy + tPy
			// Iz = Rz(t) = (1 - t)Cz + tPz

		// Then substitute the above into the line equation: Ax + By +Cz + D = 0;
	return (-1);
}

int		ft_check_for_circle(void)
{
	
	// Parametric of a sphere
	// P.x=cos(θ)sin(ϕ)
	// P.y=cos(θ)	
	// P.z=sin(θ)sin(ϕ)

	// to check if a point is inside a sphere centered around the origin
	// r2 = x2 + y2 (For a point to be inside of a circle it needs to be smaller than sqrt(r2))

	// arbitrary centre:
	// (x2 - Ox2) + (y2 - Oy2) + (z2 - Oz2) = r2
	
	return (1);
}

int		ft_tracer(int x, int y, t_env *env)
{
	int p = 0;
	float nearest = INFINITY;
	unsigned int color = 0;
	t_ray	ray;
	
	// only when cam is on [0;0;Z]
	x -= env->res.x / 2;
	y = (env->res.y / 2) - y;
	// First compute primary ray direction
	ray = ft_build_ray((t_camera*)(env->cam_list->content), x, y);
	// printf("Entering tracer\n");
	if (ft_intersect(ray, (void*)env->shapes[SPHERE]->content, &color, &nearest) != -1)
		printf("INTERSECTION FOUND\n");
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
	return (1);
}


void ft_render(t_img *img, t_env *env)
{
	int		i = 0;
	int		j = 0;
	int		d = 1;
	// float	local_x;
	// float	local_y;
	t_coord viewport;
	// float viewport_x;
	// float viewport_y;
	// float viewport_z;
	float	scale;
	float aspect_ratio = env->res.x / env->res.y;

	// scale = tan(deg2rad(((t_camera*)(env->cam_list->content))->fov * 0.5));

	// aspect_ratio = env->res.x / env->res.y;
	
	// printf("Entering rendering\n");
	// Iterate over all pixels
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			// local_x = (2 * (i + 0.5) / env->res.x * aspect_ratio * scale);
			// local_y = (1 - 2 * (j + 0.5) / env->res.y * scale); 


			// First compute primary ray direction
			// ray = ft_build_ray(i, j);
			if (ft_tracer(i, j, env))
				printf("So far so good:\ni: %d\nj: %d\n", i ,j);
				// my_pixel_put(img, i, j, 0x00ffffff); // shader function for putting the color
			j++;
		}
		i++;
	}
}
