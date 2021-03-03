/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   example.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 19:19:52 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/03 10:31:28 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// define macros for the heigth and width of the window
// For mini RT you'll be reading them from a file make them constants
// # define height 400
// # define witdh 800


// You'll be using a lot of structs within structs
// maybe an idea to write one big one and a node struct for linked lists
typedef struct 	s_img 
{
	void	*img_ptr;
	void	*mlx_ptr;
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

// faster version to write pixel to the image file
void	my_pixel_put(t_img *img, int x, int y, unsigned int colour)
{
	char	*dst;
	int		offset;

	// offset traverses the correct amount of memory to the stop in the 
	// img memory where you want to start writing pixel
	offset = y * img->line_size + x * (img->bits_per_pixel / 8);
	dst = img->address + offset;
	*(unsigned int *)dst = colour;
}

// function to close the window and exit the program
int		my_destroy_window(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->wdw_ptr);
	exit(1);
	return (0);
}

// main drawing loop
// first checks if an image already exists, if so deletes
// a new image is created and then the imag is drawn on its new position
int draw_img(t_img *img, unsigned int color)
{
	int i;
	
	if (img->img_ptr)
		mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	img->img_ptr = mlx_new_image(img->mlx_ptr, 800, 400);
	// take half the size of the image (left half, right half)
	i = img->x - img->width/2;
	while (i < (img->x + img->width/2))
	{
		my_pixel_put(img, i, img->y, color);
		i++;
	}
	i = img->y - img->height/2;
	while (i < img->height/2 + img->y)
	{
		my_pixel_put(img, img->x, i, color);
		i++;
	}
	
	mlx_put_image_to_window(img->mlx_ptr, img->wdw_ptr, img->img_ptr, 0, 0);
	return (0);
}

// function to control actions performed on the keyboard
int keypress(int kc, t_img *img)
{
	if (kc == 123 || kc == 0)
		img->x -= 5;
	else if (kc == 124 || kc == 2)
		img->x += 5;
	else if (kc == 125 || kc == 1)
		img->y += 5;
	else if (kc == 126 || kc == 13)
		img->y -= 5;
	else if (kc == 53)
		my_destroy_window(img);
		
	return (0);
}

int		main(void)
{
	// mlx_init(); start mlx up and connects it with your graphical system
	void *mlx_ptr = mlx_init();
	void *window;
	void *img_ptr;
	t_img	img;
	int i = 0;
	
	// if initialization was succesful continue
	if (mlx_ptr)
	{
		window = mlx_new_window(mlx_ptr, 800, 400, "My first MLX window");
		img_ptr = mlx_new_image(mlx_ptr, 800, 400);
	}
	if (!window)
		return (-1);

	img.address = mlx_get_data_addr(img_ptr, &img.bits_per_pixel, &img.line_size, &img.endian);

	// these vars will be read from a file
	// find a more efficient way to store them
	img.x = 400; // window width/2
	img.y = 200; // window height/2
	img.height = 30;
	img.width = 30;
	img.wdw_ptr = window;
	img.mlx_ptr = mlx_ptr;
	img.img_ptr = img_ptr;
	
	draw_img(&img, 0xffffff);
	
	mlx_hook(window, 17, 1l << 17, my_destroy_window, &img);
	mlx_hook(window, 2, 1l << 0, keypress, &img);
	
	mlx_loop_hook(mlx_ptr, draw_img, &img);
	
	// always your last call as it's an invite loop
	mlx_loop(mlx_ptr);
	return (0);
}