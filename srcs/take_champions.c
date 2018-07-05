
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


void 		take_champions(int ac, char **av, t_player *players)
{
	int fd;
	int i;

	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		check_magic(fd);
		players->name = read_alloc_size(fd, PROG_NAME_LENGTH + 4);
		print_memory(players->name, PROG_NAME_LENGTH + 4, 16, 2);
		ft_putendl(players->name);
		players->prog_size = read_alloc_size(fd, 4);
		print_memory(players->prog_size, 4, 16, 2);
		players->comment = read_alloc_size(fd, COMMENT_LENGTH + 4);
		// players->prog = read_alloc_size(fd, )
		big_hexa_2_dec(players->prog_size, 4);
		i++;
	}

}

