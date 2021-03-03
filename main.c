/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/03 13:44:38 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>


// Different components or objects to the project
		// Parsing
		// Raytracing calculations
		// Writing to the window or to a .bmp


int	main(int argc, char *argv[])
{
	//  argv[1] .rt file with description of the scene to be created
	int		fd;
	char	*line;
	int		ret = 1;
	static	t_env	env;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Open failed\n");
		exit(1);
	}
	while(ret > 0)
	{
		ret = get_next_line(fd, &line);
		// parse(line, &env);
		free(line);
	}
	// Use GNL to read from the .rt file
	// With each line check the indentifier, parseing similair to printf 
		// When parsing assign data to fitting struct
		// One struct for each of the camera, lighting & AmbLight and camera, and then one big struct containing them all
		// maybe one node struct for each shape?
		// struct for containing all shapes?
	
	// ** Use the example the to see which data types are usd for the numbers ex. int, float, etc 
	// while(1);
}