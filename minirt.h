/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/03 13:41:19 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>
#include "mlx/mlx.h"
#include <stdio.h>

// What is ambient lighting?? (kinda like the sun, awlways constant, present lighting)
// What is 3d normalized vector?? Normalizes the vector distance ex. point x:1,y:0 & x:0,y:1 nrm3dvec = x:0,7,y:0,7 (draw it out)
// Using ENUM for the project??
enum shapes{sp, pl, sq, cy, tr};


// Defining of structs
	// Structs for the enviroment
		// Resolution
typedef struct   s_res
{
	unsigned char	id; // R
	const float     x;
	const float     y;
}               t_res;

		// Ambient lighting
typedef struct   s_amb_light
{
	unsigned char    id; // A
	float			ratio; // [0.0 - 1.0]
	// colors, rgb, [0-255]
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_amb_light;

		// Camera
typedef struct	s_camera
{
	unsigned char	id; // c
	// coord of camera 
	float			x;
	float			y;
	float			z;
	float			ratio;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	fov; // [0 - 180]
}				t_camera;
	
		// Light source
typedef struct	s_light_src
{
	unsigned char	id; // l
	float			x;
	float			y;
	float			z;
	float			brightness;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	
}				t_light_src;

		// Struct containing all enviroment structs
typedef struct	s_env
{
	t_res		res;
	t_amb_light amb_light;
	t_camera	camera;
	t_light_src	light_src;
}				t_env;
	
	// Structs for shapes
		// Sphere
typedef struct s_sphere
{
	unsigned char	id;
	float			x;
	float			y;
	float			z;
	float			diam;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_sphere;

		// Plane
typedef struct s_plane
{
	unsigned char	id;
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_plane;

		// Square
typedef struct s_square
{
	unsigned char	id;
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_square;


typedef struct s_cylinder
{
	unsigned char	id;
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_cylinder;

typedef struct	s_shapes
{
	t_sphere 	sphere;
	t_plane		plane;
	t_square	square;
	t_cylinder	cyl;
}				t_shapes;



int		parse(char *line, t_env *env);
char	**ft_split_sset(char const *s, char *set);