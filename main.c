/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/07 13:35:44 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>


// Different components or objects to the project
		// Parsing
		// Error management
		// Raytracing calculations
		// Writing to the window or to a .bmp

// TODO ERROR MANAGEMENT:
	// VECT_COORDS
	// SPLIT LENGTH
	// ROUND FLOAT 2
int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		ret = 1;
	static	t_env	env;

	if (argc != 2)
	{
		printf("Usage: ./executable scene.rt");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpen failed\n");
		exit(1);
	}
	while(ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (*line != '\0')
		{
			env.spl_str = ft_split(line, ' ');
			if (!env.spl_str)
				return (-1);
			printf("parse: %d\n", parse(&env));
			free_split(env.spl_str);
		}
		free(line);
	}
	printf("RGB: %d\n", ((t_triangle*)(env.triangle_lst->content))->colors.b);

	ft_lstclear(&env.light, free);
	ft_lstclear(&env.cam_list, free);
	ft_lstclear(&env.sphere_lst, free);
	ft_lstclear(&env.plane_lst, free);
	ft_lstclear(&env.square_lst, free);
	ft_lstclear(&env.cylinder_lst, free);
	ft_lstclear(&env.triangle_lst, free);
	// while(1);
	return (0);
}