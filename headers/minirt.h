/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 10:09:33 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/17 22:45:29 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "ft_structure.h"
# include "ft_defines.h"
# include "../libft/libft.h"

void	ft_mlx_error(char *str);

int		parse(char *file_name, t_env *env);
int		parse_tree(t_env *env);
void	ft_parse_error(char *err_desc);

int		parse_res(char **spl_str, t_res *res);
int		parse_amb_light(char **spl_str, t_amb_light *am_lt);
int		parse_cam(char **spl_str, t_list **cam);
int		parse_light(char **split, t_list **light_lst);

int		parse_sphere(char **split, t_list **sphere_lst);
int		parse_plane(char **split, t_list **plane_lst);
int		parse_square(char **split, t_list **square_lst);
int		parse_cylinder(char **split, t_list **cylinder_lst);
int		parse_triangle(char **split, t_list **triangle_lst);

int		ft_run_mlx(t_env *env);


void	free_split(char **split_array);
void	ft_exit(t_env *env, char *description);

// utils/parse_utils.c
void	ass_colors(char *str, t_rgb *cols);
void	ass_coords(char *str, t_vec *coords);
int		ft_str_arr_len(char **str_array);

t_vec	create_pos(double x, double y, double z);
t_vec	ft_normalize(t_vec vec);

//utils/vec_utils.c
t_vec	ft_vec_multi_matrix(t_matrix3x3 m, t_vec vect);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_minus(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, double factor);
t_vec	vec_divide(t_vec a, double factor);
t_vec	vec_by_vec(t_vec a, t_vec b);
void	print_vec(t_vec vec, char *description);

double	ft_vec_len(t_vec coords);
double	ft_dot_product(t_vec a, t_vec b);
t_vec	ft_cross_product(t_vec a, t_vec b);
t_vec	calc_hitpoint(t_ray *primary_ray, double t);
int		ass_hitpoint(double t, t_rgb col, int id, t_hit *hit);

// utils/draw_utils.c
void	my_pixel_put(t_img *img, int x, int y, unsigned int colour);
void	ft_assign_t3rgb(t_rgb big_col, t_3rgb *small_col);

// utils/ft_color_utils.c
void	ft_color_multi(t_rgb *col, double factor);
t_rgb	ft_color_times_color(t_rgb col, t_rgb factor);
void	ft_color_check(t_rgb *col);
t_rgb	ft_colors_add(t_rgb col, t_rgb rgb);
int		ft_create_trgb(int t, int r, int g, int b);

// utils/ft_output_to_bmp.c
int		ft_put_img_to_bmp(char *file_name, t_env *env, t_3rgb *col);

// rendering/draw_shapes.c
void	ft_draw_square(t_img *img, t_square *sqr);

// rendering/ft_sphere_intersection.c
double	ft_sphere_intersect(t_sphere *sphere, t_ray *ray, t_hit *intersection);

// rendering/ft_plane_intersect.c
double	ft_plane_intersect(t_plane *plane, t_ray *ray, t_hit *intersection);

// rendering/ft_render.c
int		ass_hitpoint(double t, t_rgb col, int id, t_hit *hit);
t_ray	ft_primary_ray(t_camera *cam, double x, double y);
int		ft_intersect(t_ray ray, t_list **shape_list, t_hit *intersection);
t_rgb	ft_tracer(int x, int y, t_env *env);
int		ft_render(t_env *env);
void	ft_threading_render(t_env *env);

// rendering/ft_shadowing.c
t_ray	ft_shadow_ray(t_light *light, t_vec *hitpoint);
t_rgb	ft_shader(t_env *env, t_hit *hitp);

// rendering/ft_triangle.c
double	ft_triangle_intersect(t_triangle *triangle, t_ray *ray, t_hit *hitp);

// rednering/ft_square_intersect.c
int		ft_square_intersect(t_square *sq, t_ray *ray, t_hit *intersect);

// rednering/ft_cylinder_intersect.c
int		ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hitp);

//utils/ft_filters.o
t_3rgb	*ft_grayscale(t_3rgb *colors, int width, int height);
t_3rgb	*ft_sepia(t_3rgb *col, int width, int height);

void	ft_put_img_to_window(t_img *img, t_env *env, t_3rgb *cols);
void	ft_switch_camera(t_img *img);

#endif