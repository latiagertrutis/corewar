
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
	/* int rtn; */
	/* int i; */
	/* int mask; */

	/* // rtn |= ((nb & (0xff000000)) >> 24); */
	/* // rtn |= ((nb & (0x00ff0000)) >> 8); */
	/* // rtn |= ((nb & (0x0000ff00)) << 8); */
	/* // rtn |= ((nb & (0x000000ff)) << 24); */
	/* rtn = 0; */
	/* i = (size - 1); */
	/* mask = 0xff << (size - 1); */
	/* while (i > 0) */
	/* { */
	/* 	rtn |= ((*str & (mask)) >> (i * 8)); */
	/* 	mask = mask >> 8; */
	/* 	i -= 2; */
	/* } */
	/* i += 2; */
	/* mask = mask << 8; */
	/* while (i < size) */
	/* { */
	/* 	rtn |= ((nb & (mask)) >> (i * 8)); */
	/* 	mask = mask << 8; */
	/* 	i += 2; */
	/* } */
	/* return(rtn); */
}	
