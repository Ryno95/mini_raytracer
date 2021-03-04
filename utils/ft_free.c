#include <stdlib.h>

void	free_split(char **split_array)
{
	int i;

	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
