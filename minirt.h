/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/01 20:35:45 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>
#include "mlx/mlx.h"
#include <stdio.h>

# define IDS "RAcl"
# define ray_max 1e6
# define ray_min 1e-6


// What is ambient lighting?? (kinda like the sun, awlways constant, present lighting)
// What is 3d normalized vector?? Normalizes the vector distance ex. point x:1,y:0 & x:0,y:1 nrm3dvec = x:0,7,y:0,7 (draw it out)
// Using ENUM for the project??
enum multi_opts{SPHERE, PLANE, SQUARE, CYLINDER, TRIANGLE};
// enum env{CAM, LIGHT_SRC};

// Defining of structs
	// Basics
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


// typedef struct	s_coord
// {
// 	float			x;
// 	float			y;
// 	float			z;
// }				t_coord;

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
	float			cam_dist;
}				t_camera;
	
		// Light source
typedef struct	s_light
{
	unsigned char	id; // l
	t_coord			coords;
	float			brightness;
	t_rgb			colors;
	
}				t_light;

	
// Structs for shapes
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

void	ft_mlx_error(char *str);

// parse/parse.c
int		parse(char *file_name, t_env *env);
int		parse_tree(t_env *env);

// parse/parse_env.c
int		parse_res(char **spl_str, t_res *res);
int		parse_amb_light(char **spl_str, t_amb_light *am_lt);
int		parse_cam(char **spl_str, t_list **cam, t_res *res);
int		parse_light(char **split, t_list **light_lst);

// parse/parse_shapes.c
int		parse_sphere(char **split, t_list **sphere_lst);
int		parse_plane(char **split, t_list **plane_lst);
int		parse_square(char **split, t_list **square_lst);
int		parse_cylinder(char **split, t_list **cylinder_lst);
int		parse_triangle(char **split, t_list **triangle_lst);

// window_control/ft_window.c
int		ft_run_mlx(t_img *img, t_env *env);
int		keypress(int kc, t_img *img);
int		my_destroy_window(t_img *img);

// utils/ft_free.c
void	free_split(char **split_array);

// utils/parse_utils.c
void	ass_colors(char *str, t_rgb *cols);
void	ass_coords(char *str, t_coord *coords);
int		ft_str_arr_len(char **str_array);

// utils/ft_errors.c
void	ft_parse_error(char *err_desc);

// Utils/ft_math_utils.c
float	ft_vec_len(t_coord coords);
float	ft_round_fl(float num, int decimals);
t_coord create_pos(float x, float y, float z);
void normalize(t_vec *vec);

//utils/vec_utils.c
float	vec_len(t_coord coords);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_minus(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, float factor);
t_vec	vec_divide(t_vec a, float factor);

//utils/vec_products.c
float	dot_product(t_vec a, t_vec b);
t_vec	cross_product(t_vec a, t_vec b);


// utils/draw_utils.c
void	my_lstiter(t_list *lst, t_img *img, void (*f)(t_img *, void *));
void	my_pixel_put(t_img *img, int x, int y, unsigned int colour);

// tracer/draw_shapes.c
void	ft_draw_square(t_img *img, t_square *sqr);


//tracer/ft_tracer.c
t_ray	ft_build_ray(t_camera *cam, int x, int y);
int		ft_tracer(int x, int y, t_env *env);
void	ft_render(t_img *img, t_env *env);

//tracer/ft_sphere_intersection.c
float   ft_sphere_intersect(t_sphere *sphere, t_ray *ray);