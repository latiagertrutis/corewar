
#include "corewar.h"

void 		big_hexa_2_dec(char *str, int size)
{
	invert_bytes((void *)str, size);
	print_memory(str, size, 4, 2);
}
