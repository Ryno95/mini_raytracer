/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_structure.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:38:01 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/05 15:46:43 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

enum multi_opts{SPHERE, PLANE, TRIANGLE, SQUARE, CYLINDER};

typedef struct	s_rgb
{
	float	b;
	float	g;
	float	r;
}				t_rgb;

typedef struct	s_vec
{
	double			x;
	double			y;
	double			z;
}				t_vec;

#define t_coord t_vec

typedef struct 	s_vec4d
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4d;

typedef struct	s_quadratic
{
	double a;
	double b;
	double c;
	double discrim;
	double t1;
	double t2;
}				t_quadratic;

typedef union  s_matrix3x3
{
    double m[3][3];
	struct
	{
		t_vec right;
		t_vec up;
		t_vec forward;
	};
	
}               t_matrix3x3;

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
	double			ratio; // [0.0 - 1.0]
	t_rgb			colors;
}				t_amb_light;

typedef struct	s_camera
{
	unsigned char	id; // c
	t_coord			coords;
	t_vec			vect_coords;
	t_rgb			colors;
	unsigned char	fov; // [0 - 180]
	double			cam_dist;
}				t_camera;
	
typedef struct	s_light
{
	unsigned char	id; // l
	t_coord			coords;
	double			brightness;
	t_rgb			colors;
	
}				t_light;

typedef struct s_sphere
{
	unsigned char	id;
	double			diam;
	t_coord			center;
	t_rgb			colors;
}				t_sphere;

typedef struct s_plane
{
	unsigned char	id;
	t_coord			coords;
	t_coord			orient;
	t_rgb			colors;
}				t_plane;

typedef struct s_square
{
	unsigned char	id;
	t_coord			center;
	t_coord			orient;
	double			side_size;
	t_rgb			colors;
}				t_square;

typedef struct s_cylinder
{
	unsigned char	id;
	t_coord			center;
	t_vec			ori;
	double			r;
	double			height;
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

typedef struct	s_obj
{
	int		id;
	t_coord coords;
	t_rgb	color;
	t_vec	norm_vec3d;
	
}				t_obj;

typedef struct	s_impact_point
{
	t_rgb		color;
	t_vec		normal;
	t_coord		hitpoint;
	int			object_id;
	double		near;
	
}				t_hit;

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
	int			debug;
	int			save_to_bmp;
	int			fd;
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