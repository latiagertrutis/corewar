/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:50:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/28 21:31:40 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void search_nb(t_player *players, int nb_players, int live_nb, int j)
{
	int i;

	i = 0;
	while (i < nb_players)
	{
		if (players[i].player_nb == live_nb)
		{
			players[i].live_counter++;
			players[i].last_live = j;
		}
		i++;
	}
}

static int 			take_live_nb(t_board *board)
{
	char rtn[4];

	rtn[0] = board[0].mem;
	rtn[1] = board[1].mem;
	rtn[2] = board[2].mem;
	rtn[3] = board[3].mem;
	return((*(int *)rtn));
}

void				core_live(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short	pos;
	int 	live_nb;

	pos = pc->pc;
	live_nb = take_live_nb((arena->board) + pos + 1);
	pc->live = 0x1;
	// if (live_nb == (*((int *)(pc->reg[0]))))
		// player->live_counter++;
	search_nb(data->players, data->n_players, live_nb, data->nb_cycles);
	pc->pc = (pc->pc + 1 + DIR_SIZE) % MEM_SIZE;//live + dir
}
