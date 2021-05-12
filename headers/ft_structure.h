/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_structure.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:38:01 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 17:23:42 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <pthread.h>

enum multi_opts{SPHERE, PLANE, TRIANGLE, SQUARE, CYLINDER};

typedef struct	s_rgb
{
	int	b;
	int	g;
	int	r;
}				t_rgb;

typedef struct	s_3rgb
{
	uint8_t	b;
	uint8_t g;
	uint8_t r;
}				t_3rgb;

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

typedef struct	s_filters
{
	int8_t sepia;
	int8_t grayscale;
}				t_filters;	

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
	t_3rgb		*col_array;
	int			debug;
	int			save_to_bmp;
	int			fd;
	t_filters	filters;
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
	t_env	*env;
}				t_img;


typedef struct	s_bmp_file_header
{
    uint8_t   	name[2]; // should be "BM"
    uint32_t	file_size; // height * width
    uint16_t	bmp_def; // defaults to 0
    uint16_t	bmp_def2; // defaults to 0
    uint32_t	offset; // info + file header
}				t_bmp_file_header;


typedef struct 	s_bmp_info_header
{
	uint32_t info_header_size; // 40
	uint32_t width; // height and width of res
	uint32_t height;
	uint16_t planes; // should be 1
	uint16_t bit_count;  // 1, 4, 8,16,24 or (32)
	uint32_t compression; // 0
	uint32_t img_size; //possible zero or something?
	uint32_t ppm_x; // can be zero or set to ppmconversionfactor
	uint32_t ppm_y; // can be zero
	uint32_t color_used; // 0
	uint32_t important; // if set to zero every color is important
}				t_bmp_info_header;

typedef	struct	s_thread
{
	pthread_t	tid;
	int			id;
	t_env 		*env;
}				t_thread;

