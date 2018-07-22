/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/22 13:18:35 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char op_nb;

	op_nb = (arena->board[pc->pc % MEM_SIZE].mem) - 1;
	if (pc->wait_cycles > 1)
	{
		pc->wait_cycles--;
		return ;
	}
	else if (pc->wait_cycles == 1)
	{
		pc->wait_cycles--;
		data->func[op_nb](player, pc, arena);
	}
	else
	{
		if (op_nb <= 15)
			pc->wait_cycles += (data->op[op_nb].mana) + 1;
		else
			pc->pc = (pc->pc + 1) % MEM_SIZE;
	}
}

void 				exe_players(t_data *data)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int t;

	i = 0;
	fill_r1(data);
	print_board(data, data->arena->board);
	while(i < 500000)
	{
		t = 0;
		while (t < 500000)//data->cycle_to_die)
		{

			// usleep(100);
			j = 0;
			while(j < data->n_players)
			{
				k = 0;
				while (k < data->players[j].nb_pc)
				{
					exe_pc((data->players) + j, (data->players[j].pc) + k, data->arena, data);
					k++;
				}
				j++;
			}
			i++;
			data->nb_cycles = i;
			t++;
			write(1, "\x1b[H\x1b[2J", 7);
			print_board(data, data->arena->board);
		}
		check_live_count(data->players, data->n_players);
		data->cycle_to_die -= CYCLE_DELTA;
	}
}
