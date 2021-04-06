/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_structure.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:38:01 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/05 20:31:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

enum multi_opts{SPHERE, PLANE, SQUARE, CYLINDER, TRIANGLE};

typedef union	u_rgb
{
	unsigned int rgb;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	t;
	};
}				t_rgb;

typedef struct	s_vec
{
	float			x;
	float			y;
	float			z;
}				t_vec;

#define t_coord t_vec

typedef struct	s_ray
{
	t_coord		origin;
	t_vec		direction;
}				t_ray;

typedef struct   s_res
{
	unsigned char	id; // R
	int			    x;
	int			    y;
}               t_res;

typedef struct   s_amb_light
{
	unsigned char    id; // A
	float			ratio; // [0.0 - 1.0]
	// colors, rgb, [0-255]
	t_rgb			colors;
}				t_amb_light;

typedef struct	s_camera
{
	unsigned char	id; // c
	t_coord			coords;
	t_vec			vect_coords;
	t_rgb			colors;
	unsigned char	fov; // [0 - 180]
	float			cam_dist;
}				t_camera;
	
typedef struct	s_light
{
	unsigned char	id; // l
	t_coord			coords;
	float			brightness;
	t_rgb			colors;
	
}				t_light;

typedef struct s_sphere
{
	unsigned char	id;
	float			diam;
	t_coord			coords;
	t_rgb			colors;
}				t_sphere;

typedef struct s_plane
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	t_rgb			colors;
}				t_plane;

typedef struct s_square
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	float			side_size;
	t_rgb			colors;
}				t_square;

typedef struct s_cylinder
{
	unsigned char	id;
	t_coord			coords;
	t_coord			vect_coords;
	float			diamtr;
	float			height;
	t_rgb			colors;
}				t_cylinder;

typedef struct 	s_triangle
{
	unsigned char	id;
	t_coord			frst_pnt;
	t_coord			scnd_pnt;
	t_coord			thrd_pnt;
	t_rgb			colors;
}				t_triangle;

typedef struct	s_shapes
{
	t_sphere 	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cyl;
}				t_shapes;

typedef struct	s_env
{
	char		**spl_str;
	t_res		res;
	t_amb_light amb_light;
	t_list		*cam_list;
	t_list		*light;
	t_list		*shapes[5];
	t_list		*sphere_lst;
	t_list		*plane_lst;
	t_list		*square_lst;
	t_list		*cylinder_lst;
	t_list		*triangle_lst;
}				t_env;

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

typedef	struct	s_img
{
	void	*mlx_ptr;
	void	*img_ptr;
	void	*wdw_ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		height;
	int		width;
	int		x;
	int		y;
}				t_img;