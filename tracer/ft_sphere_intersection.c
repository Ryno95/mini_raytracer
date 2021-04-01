/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/01 21:31:31 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float   ft_sphere_intersect(t_sphere *sphere, t_ray *ray)
{
    // sphere center "c" = (Cx, Cy, Cz)
    // sphere radius "R"
    // (x2 - Orix2) + (y2 - Oriy2) + (z2 - Oriz2) - r2 = 0
    // dot_product(point, ray->origin) - (sphere->diam * sphere->diam) = 0;
    // printf("entering Sphere Inter\n");
    float t = 1e-5;
    float a; // always 1
    float b;
    float c;
    float discrim;

    a = dot_product(ray->direction, ray->direction);
    b = dot_product(vec_multiply(ray->direction, 2), vec_minus(ray->origin, sphere->coords));
    c = dot_product(vec_minus(ray->origin, sphere->coords), vec_minus(ray->origin, sphere->coords)) - (sphere->diam * sphere->diam);
    discrim = b*b - 4*a*c;
    if (discrim < 0)
        return (0);

    t = (-b + sqrt(discrim)) / (2*a);
    // if ((-b - sqrt(discrim)) / (2*a) < t && ((-b - sqrt(discrim)) / (2*a)) > 0)
    //     t = (-b - sqrt(discrim)) / (2*a);
    // a * (t * t) b * t + c
    // printf("t: %f\n", t);
    
    // printf("T: %f\n", t);
    if (t != 1e-5)
        return (t);
    return (0);
}


// int			intersect_sphere(t_ray ray, t_shape *sphere)
// {
// 	t_v3	c_vec;
// 	double	a;
// 	double	b;
// 	double	c;
// 	c_vec = vec3_sub(ray.o, sphere->o);
// 	c = vec3_len(c_vec);
// 	a = vec3_dot(c_vec, ray.d);
// 	b = sqrt(c * c - a * a);
// 	if (sphere->r >= b)
// 		return (1);
// 	return (0);
// }