/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:49:00 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/10 21:27:49 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// static int	check_args(t_data *data, char **av, int i)
// {
// 	if (*(av[i + 1]) == '-')
// 	{
		
// 	}
// }

void 		take_champions(t_data *data, char **av)
{
	int 			fd;
	unsigned int	i;

	i = 0;
	while (i < data->n_players)
	{
		// if (check_args(data, av, i))
		// {
		// 	av += 2;
		// 	continue ;
		// }
		data->players[i].id = i;
		fd = open(av[i + 1], O_RDONLY);
		check_magic(fd);
		ft_printf("{red}NOMBRE:\n{eoc}");
		data->players[i].name = read_alloc_size(fd, PROG_NAME_LENGTH + 4);
		// print_memory(data->players[i].name, PROG_NAME_LENGTH + 4, 16, 2);
		ft_putendl(data->players[i].name);
		ft_printf("{red}PROG SIZE:\n{eoc}");
		data->players[i].prog_size = get_prog_size(fd);
		big_hexa_2_dec((char *)(&(data->players[i].prog_size)), sizeof(unsigned int));
//		ft_printf("{red}COMMENT:\n{eoc}");
		data->players[i].comment = read_alloc_size(fd, COMMENT_LENGTH + 4);
//		print_memory(players->comment, COMMENT_LENGTH + 4, 16, 2);
		ft_printf("{red}PROG:\n{eoc}");
		data->players[i].prog = read_alloc_size(fd, data->players[i].prog_size);
		 print_memory(data->players[i].prog, data->players[i].prog_size, 16, 2);
		i++;
	}

}
