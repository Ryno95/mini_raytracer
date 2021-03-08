/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/07 22:07:34 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Psuedo code for a raytracing algorithm

void tracer()
{
	int i,j = 0;
	int res_x, res_y = 0; // (width and height)
	while (i < res_y)
	{
		while (j < res_x)
		{
			// First compute primary ray direction
			

			// Shoot primary ray in the scene in search for an intersection
			

			// If a hit is found compute the illumination
			
			
			// pixel[i][j] = object->color * light.brightness
			j++;
		}
		i++;
	}
	
}