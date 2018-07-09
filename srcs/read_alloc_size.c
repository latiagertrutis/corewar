#include "corewar.h"

char *read_alloc_size(int fd, int size)
{
	char *rtn;

	rtn = (char *)malloc(sizeof(char) * size);
	read(fd, rtn, size);
	return (rtn);
}