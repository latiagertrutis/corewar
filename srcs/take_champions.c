
#include "corewar.h"

static void	check_magic(int fd)
{
	char buff[4];

	read(fd, buff, 4);
	if (buff[0] == (char)0x00 && buff[1] == (char)0xEA
		&& buff[2] == (char)0x83 && buff[3] == (char)0xF3)
		ft_putendl("TRUE: magic number correct");
	else
		ft_putendl("FALSE: magic number incorrect");
}

static char *read_alloc_size(int fd, int size)
{
	char *rtn;

	rtn = (char *)malloc(sizeof(char) * size);
	read(fd, rtn, size);
	return (rtn);
}


void 		take_champions(t_data *data, char **av)
{
	int 			fd;
	unsigned int	i;

	i = 1;
	while (i < data->n_players + 1)
	{
		fd = open(av[i], O_RDONLY);
		check_magic(fd);
		ft_printf("{red}NOMBRE:\n{eoc}");
		data->players[i - 1].name = read_alloc_size(fd, PROG_NAME_LENGTH + 4);
		print_memory(data->players[i - 1].name, PROG_NAME_LENGTH + 4, 16, 2);
		ft_putendl(data->players[i - 1].name);
		ft_printf("{red}PROG SIZE:\n{eoc}");
		data->players[i - 1].prog_size = *((unsigned int *)read_alloc_size(fd, sizeof(unsigned int)));
		big_hexa_2_dec((char *)(&(data->players[i - 1].prog_size)), sizeof(unsigned int));
//		ft_printf("{red}COMMENT:\n{eoc}");
		data->players[i - 1].comment = read_alloc_size(fd, COMMENT_LENGTH + 4);
//		print_memory(players->comment, COMMENT_LENGTH + 4, 16, 2);
		ft_printf("{red}PROG:\n{eoc}");
		data->players[i - 1].prog = read_alloc_size(fd, data->players[i - 1].prog_size);
		print_memory(data->players[i - 1].prog, data->players[i - 1].prog_size, 16, 2);
		i++;
	}

}
