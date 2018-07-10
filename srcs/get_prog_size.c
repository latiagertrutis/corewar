#include "corewar.h"

int 	get_prog_size(int fd)
{
	char	*str_size;
	int 	i_size;

	str_size = read_alloc_size(fd, sizeof(unsigned int));
	i_size = *((unsigned int *)str_size);
	free(str_size);
	if (i_size > CHAMP_MAX_SIZE)
		ft_error("Champ too big");
	return(i_size);
}
