/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/21 15:54:50 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "ft_structure.h"
// #include "./parse/ft_parse.h"
// #include "./tracer/ft_render.h"
// #include "./utils/ft_utils.h"
#include <math.h>
#include "mlx/mlx.h"
#include <stdio.h>

# define IDS "RAcl"
# define ray_max 1e6
# define ray_min 1e-6


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
t_vec 	normalize(t_vec vec);

//utils/vec_utils.c
float	vec_len(t_coord coords);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_minus(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, float factor);
t_vec	vec_divide(t_vec a, float factor);
void	print_vec(t_vec vec, char *description);

//utils/vec_products.c
float	dot_product(t_vec a, t_vec b);
t_vec	cross_product(t_vec a, t_vec b);
t_vec   calc_hitpoint(t_ray *primary_ray, float t);


// utils/draw_utils.c
void	my_lstiter(t_list *lst, t_ray *ray, unsigned int *nearest ,void (*f)(t_list *, t_ray * ,void *));
void	my_pixel_put(t_img *img, int x, int y, unsigned int colour);

// utils/ft_color_utils.c
void	color_multi(t_rgb *col, float factor);
t_rgb	color_times_color(t_rgb col, t_rgb factor);
void	color_check(t_rgb *col);
t_rgb	colors_add(t_rgb col, t_rgb rgb);
int		create_trgb(int t, int r, int g, int b);

// rendering/draw_shapes.c
void	ft_draw_square(t_img *img, t_square *sqr);


// rendering/ft_tracer.c
t_ray	ft_build_ray(t_camera *cam, int x, int y);
int		ft_tracer(int x, int y, t_env *env, t_rgb *color);
void	ft_render(t_img *img, t_env *env);

// rendering/ft_sphere_intersection.c
float	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_impact_point *intersection);

// rendering/ft_plane_intersect.c
float	ft_plane_intersect(t_plane *plane, t_ray *ray, t_impact_point *intersection);

// rendering/ft_render.c
t_ray	ft_primary_ray(t_camera *cam, int x, int y);
int		ft_intersect(t_ray ray, t_list **shape_list, t_impact_point *intersection);
int		ft_tracer(int x, int y, t_env *env, t_rgb *color);
void    ft_render(t_img *img, t_env *env);
void	ft_print_color(t_rgb vector);

// rendering/ft_shadowing.c
t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint);
t_rgb	ft_shading(t_env *env, t_impact_point *intersection, t_ray shadow_ray, t_light *light);

// debug/debugray.c
void	ft_print_vect(t_vec vector, char *pre);
int    ft_debugray(int keycode, int x, int y, t_env *scene);

// rendering/ft_triangle.c
float	ft_triangle_intersect(t_triangle *triangle, t_ray *ray, t_impact_point *intersection);

// rendering/ft_cylinder_intersect.c
int     ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_impact_point *hitp);