/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere_intersection.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:10:49 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/31 18:21:54 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float   ft_sphere(t_sphere *sphere, t_ray *ray)
{
    // sphere center "c" = (Cx, Cy, Cz)
    // sphere radius "R"
    // (x2 - Orix2) + (y2 - Oriy2) + (z2 - Oriz2) - r2 = 0
    // dot_product(point, ray->origin) - (sphere->diam * sphere->diam) = 0;
    printf("entering Sphere Inter\n");
    float t1 = 1e-6;
    float t2 = 1e-6;
    t_coord ori = ray->origin;
    t_vec dir = ray->direction;
    float radius = sphere->diam;
    float a; // always 1
    float b;
    float c;
    float discrim;

    a = dot_product(dir, dir);
    b = dot_product(vec_multiply(dir, 2), vec_minus(ori, sphere->coords));
    c = dot_product(vec_minus(ori, sphere->coords), vec_minus(ori, sphere->coords)) - (radius * radius);
    printf("X:%f\nY:%f\nZ:%f\n", sphere->coords.x, sphere->coords.y, sphere->coords.z);
    discrim = b*b - 4*a*c;
    if (discrim < 0)
        return (0);

    t1 = (-b + sqrt(discrim)) / (2*a);
    t2 = (-b - sqrt(discrim)) / (2*a);
    // a * (t * t) b * t + c
    printf("t1: %f\nt2: %f\n", t1, t2);

    float t = INFINITY;
    



    // t_coord point = vec_add(ori, vec_multiply(t * dir));

    





    // pow(x - Cx, 2) + pow(y-Cy, 2) + pow(z-Cz, 2) - pow(R, 2) = 0
    // dot_product(p-c, p-c) - pow(R, 2) = 0
    // quadratic for a sphere
    // pow(a*t, 2) + b*t + c = 0
    if (t1 < t2 && t1 > 0)
        return (t1);
    else if (t2 < t1 && t2 > 0)
        return (t2);
    else if (t1 = t2)
        return (t1);
    return (-1);
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