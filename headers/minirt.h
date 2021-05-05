/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/05 16:58:12 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "ft_structure.h"
#include "../gnl/get_next_line.h"
#include "../libft/libft.h"

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

// utils/ft_matrices.c
// t_matrix4x4  ft_matrix_multi(t_matrix4x4 a, t_matrix4x4 b);
t_vec     ft_vec_multi_matrix(t_matrix3x3 m, t_vec vect);

// utils/ft_free.c
void	free_split(char **split_array);

// utils/parse_utils.c
void	ass_colors(char *str, t_rgb *cols);
void	ass_coords(char *str, t_coord *coords);
int		ft_str_arr_len(char **str_array);

// utils/ft_errors.c
void	ft_parse_error(char *err_desc);

// Utils/ft_math_utils.c
double	ft_vec_len(t_coord coords);
double	ft_round_fl(double num, int decimals);
t_coord create_pos(double x, double y, double z);
t_vec 	normalize(t_vec vec);

//utils/vec_utils.c
double	vec_len(t_coord coords);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_minus(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, double factor);
t_vec	vec_divide(t_vec a, double factor);
void	print_vec(t_vec vec, char *description);

//utils/vec_products.c
double	dot_product(t_vec a, t_vec b);
t_vec	cross_product(t_vec a, t_vec b);
t_vec   calc_hitpoint(t_ray *primary_ray, double t);


// utils/draw_utils.c
void	my_lstiter(t_list *lst, t_ray *ray, unsigned int *nearest ,void (*f)(t_list *, t_ray * ,void *));
void	my_pixel_put(t_img *img, int x, int y, unsigned int colour);

// utils/ft_color_utils.c
void	ft_color_multi(t_rgb *col, double factor);
t_rgb	ft_color_times_color(t_rgb col, t_rgb factor);
void	ft_color_check(t_rgb *col);
t_rgb	ft_colors_add(t_rgb col, t_rgb rgb);
int		ft_create_trgb(int t, int r, int g, int b);

// utils/ft_output_to_bmp.c
int	create_bmp(char *file_name, t_rgb **cols);
int	write_bmp_header(int fd, int width, int height);

// rendering/draw_shapes.c
void	ft_draw_square(t_img *img, t_square *sqr);


// rendering/ft_tracer.c
// t_ray	ft_build_ray(t_camera *cam, int x, int y);
// int		ft_tracer(int x, int y, t_env *env, t_rgb *color);
// void	ft_render(t_img *img, t_env *env);

// rendering/ft_sphere_intersection.c
double	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_hit *intersection);

// rendering/ft_plane_intersect.c
double	ft_plane_intersect(t_plane *plane, t_ray *ray, t_hit *intersection);

// rendering/ft_render.c
void	ass_hitpoint(double t, t_rgb col, int id, t_hit *hit);
t_ray	ft_primary_ray(t_camera *cam, double x, double y);
int		ft_intersect(t_ray ray, t_list **shape_list, t_hit *intersection);
t_rgb	ft_tracer(int x, int y, t_env *env);
t_rgb   **ft_render(t_img *img, t_env *env);


// rendering/ft_shadowing.c
t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint);
// t_rgb	ft_shading(t_env *env, t_hit *intersection, t_ray ray, t_light *light);
// t_rgb	ft_shader(t_env *env, t_hit *hitp);
t_rgb	ft_shader(t_env *env, t_hit *hitp);

// debug/debugray.c
void	ft_print_vect(t_vec vector, char *pre);
// int    ft_debugray(int keycode, int x, int y, t_env *scene);
void	ft_print_color(t_rgb vector);

// rendering/ft_triangle.c
double	ft_triangle_intersect(t_triangle *triangle, t_ray *ray, t_hit *hitp);

// rednering/ft_square_intersect.c
int		ft_square_intersect(t_square *sq, t_ray *ray, t_hit *intersect);

// rednering/ft_cylinder_intersect.c
int		ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hitp);
int     ft_in_range(t_cylinder *cy, double t,  t_ray *ray);