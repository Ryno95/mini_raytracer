// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   ft_utils.h                                         :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2021/04/02 13:37:01 by rmeiboom      #+#    #+#                 */
// /*   Updated: 2021/04/02 13:56:34 by rmeiboom      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../ft_structure.h"

// void	free_split(char **split_array);

// // utils/parse_utils.c
// void	ass_colors(char *str, t_rgb *cols);
// void	ass_coords(char *str, t_coord *coords);
// int		ft_str_arr_len(char **str_array);

// // utils/ft_errors.c
// void	ft_parse_error(char *err_desc);

// // Utils/ft_math_utils.c
// double	ft_vec_len(t_coord coords);
// double	ft_round_fl(double num, int decimals);
// t_coord create_pos(double x, double y, double z);
// void normalize(t_vec *vec);

// //utils/vec_utils.c
// double	vec_len(t_coord coords);
// t_vec	vec_add(t_vec a, t_vec b);
// t_vec	vec_minus(t_vec a, t_vec b);
// t_vec	vec_multiply(t_vec a, double factor);
// t_vec	vec_divide(t_vec a, double factor);
// void 	print_vec(t_vec vec);

// //utils/vec_products.c
// double	dot_product(t_vec a, t_vec b);
// t_vec	cross_product(t_vec a, t_vec b);


// // utils/draw_utils.c
// void	my_lstiter(t_list *lst, t_img *img, void (*f)(t_img *, void *));
// void	my_pixel_put(t_img *img, int x, int y, unsigned int colour);