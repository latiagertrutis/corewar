/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/10 18:06:05 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_data *data, int j)
{
	int pos;

	pos = (data->arena->board[data->players[j].pc].mem) - 1;
	if (data->players[j].wait_cycles > 1)
	{
		data->players[j].wait_cycles--;
		return ;
	}
	else if (data->players[j].wait_cycles == 1)
	{
		data->players[j].wait_cycles--;
		func[pos](data->players + j, data->op[pos], data->arena);
	}
	else
	{
		if(pos >= 0 && pos <= 15)
			data->players[j].wait_cycles += data->op[pos].mana;
		else
			data->players[j].pc++;
	}
}

void 				exe_players(t_data *data)
{
	int i;
	int j;

	i = 0;
	print_board(&data, data.arena->board);
	while(i < 20)
	{
		usleep(100000);
		j = 0;
		while(j < data->n_players)
		{
			exe_pc(data, j)
		}
		i++;
		// write(1, "\x1b[H\x1b[2J", 7);
		// print_board(&data, data.arena->board);

	}
}