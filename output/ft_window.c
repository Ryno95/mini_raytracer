/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:31:15 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/07 20:27:59 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../mlx/mlx.h"

int	ft_run_mlx(t_img *img, t_env *env)
{
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		ft_mlx_error("Couldn't init mlx");
	img->wdw_ptr = mlx_new_window(img->mlx_ptr, env->res.x, env->res.y, "RT");
	img->img_ptr = mlx_new_image(img->mlx_ptr, env->res.x, env->res.y);
	if (!img->wdw_ptr)
		ft_mlx_error("Couldn't init window");
	img->address = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_size, &img->endian);
	return (0);
}

int	keypress(int kc, t_img *img, t_env *env)
{
	if (kc == 124 || kc == 2)
	{
		env->cam_list->next;
		printf("KEY-PRESSED");
		// ft_render(env);
	}
	else if (kc == 53)
		my_destroy_window(img);
	return (0);
}



int	my_destroy_window(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->wdw_ptr);
	exit(1);
}