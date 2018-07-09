
#include "corewar.h"


void 		big_hexa_2_dec(char *str, int size)
{

	print_memory(str, size, 4, 2);
	invert_bytes((void *)str, size);
	print_memory(str, size, 4, 2);

	// i = str[4];
	// ft_putnbr(i);
	// while (i > 0)
	// {
	// 	ft_
	// 	i--;
	// }ma

}
