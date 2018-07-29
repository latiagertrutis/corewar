/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:49:00 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/29 17:40:26 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_magic(int fd)
{
	char buff[4];

	read(fd, buff, 4);
	if (buff[0] == (char)0x00 && buff[1] == (char)0xEA
		&& buff[2] == (char)0x83 && buff[3] == (char)0xF3)
		return ;
	else
		ft_error("FALSE: magic number incorrect\n");
}

void		get_champion(t_data *data, char **av, int j, int i)
{
	int fd;
	int ply_nb;

	ft_printf("%sPlayer %d: ", data->palete[j + 1], j + 1);
	fd = open(av[i], O_RDONLY);
	check_magic(fd);
	data->players[j].name = read_alloc_size(fd, PROG_NAME_LENGTH + 4);
	ft_putstr(data->players[j].name);
	ft_printf(", Player number: ");
	ply_nb = data->players[j].player_nb;
	if (ply_nb < 0)
		invert_bytes(&ply_nb, sizeof(int));
	ft_putnbr(ply_nb);
	ft_printf(", PROG SIZE: ");
	data->players[j].prog_size = get_prog_size(fd);
	ft_printf("%u", data->players[j].prog_size);
	data->players[j].comment = read_alloc_size(fd, COMMENT_LENGTH + 4);
	data->players[j].prog = read_alloc_size(fd, data->players[j].prog_size);
	ft_printf(", PROG: ");
	print_memory(data->players[j].prog, data->players[j].prog_size, data->players[j].prog_size, 1);
	ft_putchar('\n');
	ft_printf("{eoc}");
}

void 		take_champions(t_data *data, char **av, int ac)
{
	
	unsigned int	i;
	unsigned int 	j;

	i = 1;
	j = 0;
	while (i < ac && j < data->n_players)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] && av[i][1] == 'd')
			{
				i++;
				if (i < ac)
				{
					if (!(data->dump = ft_atoi(av[i])))
						ft_error("Can't read source file -d\n");
				}
				else
					ft_error("Can't read source file -d\n");
			}
			else if (av[i][1] && av[i][1] == 'n')
			{
				i++;
				if (i < ac)
				{
					if (!(data->players[j].player_nb = ft_atoi(av[i])))
						ft_error("Can't read source file -n\n");
				}
				else
					ft_error("Can't read source file -n\n");
			}
			i++;
		}
		else
		{
			get_champion(data, av, j, i);
			j++;
			i++;
		}
	}

}
