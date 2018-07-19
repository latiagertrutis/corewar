/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:50:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/18 20:33:20 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int 	take_live_nb(t_board *board)
{
	char rtn[4];

	rtn[0] = board[3].mem;
	rtn[1] = board[2].mem;
	rtn[2] = board[1].mem;
	rtn[3] = board[0].mem;
	return(*((int *)rtn));
}

void	core_live(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned short	pos;
	int 			live_nb;

	pos = pc->pc;
	live_nb = take_live_nb((arena->board) + pos + 1);
	
	ft_printf("live: %d", live_nb);
	if (live_nb == *((int *)(pc->reg[0])))
	{
		player->live_counter++;
		ft_printf("Player %d alive", player->id);
	}
	pc->pc += 5;
}
