/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/06 22:44:52 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>
#include "mlx/mlx.h"
#include <stdio.h>

# define IDS "RAcl"

// What is ambient lighting?? (kinda like the sun, awlways constant, present lighting)
// What is 3d normalized vector?? Normalizes the vector distance ex. point x:1,y:0 & x:0,y:1 nrm3dvec = x:0,7,y:0,7 (draw it out)
// Using ENUM for the project??
enum multi_opts{CAMERA, LIGHT, SPHERE, PLANE, SQAURE, CYLINDER, TRIANGLE};
// enum env{CAM, LIGHT_SRC};


// Defining of structs
	// Basics
typedef struct	s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_rgb;

typedef struct	s_coord
{
	float			x;
	float			y;
	float			z;
}				t_coord;


	// Structs for the enviroment
		// Resolution
typedef struct   s_res
{
	unsigned char	id; // R
	int			    x;
	int			    y;
}               t_res;

		// Ambient lighting
typedef struct   s_amb_light
{
	unsigned char    id; // A
	float			ratio; // [0.0 - 1.0]
	// colors, rgb, [0-255]
	t_rgb			colors;
}				t_amb_light;

		// Camera
typedef struct	s_camera
{
	unsigned char	id; // c
	// coord of camera 
	t_coord			coords;
	t_coord			vect_coords;
	t_rgb			colors;
	unsigned char	fov; // [0 - 180]
}				t_camera;
	
		// Light source
typedef struct	s_light
{
	unsigned char	id; // l
	t_coord			coords;
	float			brightness;
	t_rgb			colors;
	
}				t_light;

		// Struct containing all enviroment structs
typedef struct	s_env
{
	char		**spl_str;
	t_res		res;
	t_amb_light amb_light;
	t_list		*cam_list;
	t_list		*light;
}				t_env;
	
	// Structs for shapes
		// Sphere
typedef struct s_sphere
{
	unsigned char	id;
	float			diam;
	t_coord			coords;
	t_rgb			colors;
}				t_sphere;

		// Plane
typedef struct s_plane
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	t_rgb			colors;
}				t_plane;

		// Square
typedef struct s_square
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	t_rgb			colors;
}				t_square;


typedef struct s_cylinder
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	t_rgb			colors;
}				t_cylinder;

typedef struct	s_shapes
{
	t_sphere 	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cyl;
}				t_shapes;

typedef struct 	s_data
{
	char		**spl_str;
	t_res		res;
	t_amb_light amb_light;
	t_camera	*camera;
	t_list		*light;
	t_sphere 	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cyl;
}				t_data;

int		parse(t_env *env);
char	**ft_split_sset(char const *s, char *set);
void	free_split(char **split_array);
void	ass_colors(char *str, t_rgb *cols);
void	ass_coords(char *str, t_coord *coords);
float	ft_vec_len(t_coord coords);
void	ft_parse_error(char *err_desc);