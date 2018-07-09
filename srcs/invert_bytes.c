
#include "corewar.h"

void		invert_bytes(void *arr, const size_t size)
{
	char 	*c_arr;
	char 	aux;
	size_t	i;

	c_arr = (char *)arr;
	i = 0;
	while (i < size / 2)
	{
		aux = c_arr[i];
		c_arr[i] = c_arr[size - i -1];
		c_arr[size - i -1] = aux;
		i++;
	}
}	
