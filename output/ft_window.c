/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:31:15 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 15:41:40 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../mlx/mlx.h"

void	ft_put_img_to_window(t_img *img, t_env *env, t_3rgb *cols)
{
	int i;
	int j;
	int pos;
	int color;

	if (env->filters.sepia)
		cols = ft_sepia(cols, env->res.x, env->res.y);
	else if (env->filters.grayscale)
		cols = ft_grayscale(cols, env->res.x, env->res.y);
	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			pos = i * env->res.x + j;
			color = ft_create_trgb(0, cols[pos].r, cols[pos].g, cols[pos].b);
			my_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->wdw_ptr, img->img_ptr, 0, 0);
}

void	ft_switch_camera(t_img *img)
{
	if (img->env->cam_list->next)
		img->env->cam_list = img->env->cam_list->next;
	ft_threading_render(img->env);
	ft_put_img_to_window(img, img->env, img->env->col_array);
	return ;
}

int	keypress(int kc, t_img *img)
{
	if (kc == 124 || kc == 2)
		ft_switch_camera(img);
	else 
	if (kc == 53)
		my_destroy_window(img);
	return (0);
}

int	my_destroy_window(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->wdw_ptr);
	exit(1);
}

int	ft_run_mlx(t_env *env)
{
	t_img img;
	
	img.mlx_ptr = mlx_init();
	if (!img.mlx_ptr)
		ft_mlx_error("Couldn't init mlx");
	img.wdw_ptr = mlx_new_window(img.mlx_ptr, env->res.x, env->res.y, "RT");
	if (img.img_ptr)
		mlx_destroy_image(img.mlx_ptr, img.img_ptr);
	img.img_ptr = mlx_new_image(img.mlx_ptr, env->res.x, env->res.y);
	if (!img.wdw_ptr)
		ft_mlx_error("Couldn't init window");
	img.address = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	img.env = env;
	ft_put_img_to_window(&img, img.env, env->col_array);
	mlx_hook(img.wdw_ptr, 17, 1l << 17, my_destroy_window, &img);
	mlx_hook(img.wdw_ptr, 2, 1l << 0, keypress, &img);
	// mlx_loop_hook(img.mlx_ptr, ft_render, &env);
	mlx_loop(img.mlx_ptr);
	return (0);
}
