/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 23:21:36 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/14 01:59:26 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_player_status(t_player *players, t_data *data)
{
	int i;

	i = 0;
	while(i < data->n_players)
	{
		ft_putstr(data->palete[(int)players[i].id + 1]);
		ft_printf("Player nb: %d, name:%s, lives: %d\n"
			, players[i].player_nb, players[i].name, players[i].live_counter);
		ft_putstr("\033[0m ");
		i++;
	}
}

static void	print_pcs(t_data *data, size_t i, int j)
{
	unsigned int k;

	k = 0;
	while (k < data->n_players)
	{
		if (data->players[k].pc == (i + j))
			ft_putstr("\033[48;5;2m");
		k++;
	}
}

void		print_board(t_data *data, t_board *board)
{
	size_t			i;
	int 			j;
	char 			*hexa;

	hexa = "0123456789abcdef";
	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			ft_putstr(data->palete[(int)board[i + j].id]);
			print_pcs(data, i, j);
			ft_putchar(hexa[board[i + j].mem / 16]); //%16?
			ft_putchar(hexa[board[i + j].mem % 16]);
			ft_putstr("\033[0m ");
			j++;
		}
		ft_putchar('\n');
		i += 64;
	}

	ft_putstr("\n\nNumber of cycles: ");
	ft_putnbr(data->nb_cycles);
	ft_putchar('\n');
	print_player_status(data->players, data);
}
