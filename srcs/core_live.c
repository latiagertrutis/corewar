/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:50:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/11 21:51:01 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int 	take_live_nb(t_board *board)
{
	char rtn[4];

	rtn[0] = board + 3;
	rtn[1] = board + 2;
	rtn[2] = board + 1;
	rtn[3] = board;
	return(*((int *)rtn));
}

void	core_live(t_player *player, t_op op, t_arena *arena)
{
	unsigned short	pos;
	int 			live_nb;

	pos = player->pc;
	live_nb = take_live_nb((arena->board) + pos + 1);
	ft_printf("live: %d", live_nb);
	if (live_nb == 1) //== content register 1
	{
		data->players[i].live_counter++;
		ft_printf("Player %d alive", player->id);
	}
	player->pc += 5;
}
