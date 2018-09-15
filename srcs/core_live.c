/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:50:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/09/15 22:10:18 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void search_nb(t_player *players, const unsigned int nb_players, const int32_t live_nb, const unsigned int nb_cycles)
{
	unsigned int i;

	i = 0;
	while (i < nb_players)
	{
		//DEBUGGER
		/* ft_putstr("numero de jugador: "); */
		/* ft_putnbr(players[i].player_nb); */
		/* ft_putchar(' '); */
		/* ft_putstr("take number"); */
		/* ft_putnbr(live_nb); */
		/* ft_putchar('\n'); */
		if (players[i].player_nb == live_nb)
		{
			players[i].live_counter++;
			players[i].last_live = nb_cycles;
			players[i].live_call = 0x1;
			//SE PUEDEN REPETIR LOS NUMEROS DE JUGADORES??
			return ;
		}
		i++;
	}
}

static int32_t 			take_live_nb(t_board *board, const size_t pos)
{
	char rtn[4];

	rtn[0] = board[pos % MEM_SIZE].mem;
	rtn[1] = board[(pos + 1) % MEM_SIZE].mem;
	rtn[2] = board[(pos + 2) % MEM_SIZE].mem;
	rtn[3] = board[(pos + 3) % MEM_SIZE].mem;
	return((*(int32_t *)rtn));
}

void				core_live(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short	pos;
	int32_t 		live_nb;


	// DEBUGGER
	/* ft_putstr("pc id: "); */
	/* ft_putnbr((int)pc->id); */
	/* ft_putchar('\n'); */

	/* ft_putstr("pc pos: "); */
	/* ft_putnbr((int)pc->pc); */
	/* ft_putchar('\n'); */

	/* ft_putstr("pc reg: "); */
	/* ft_putnbr((int)pc->pc); */
	/* ft_putchar('\n'); */

	pos = pc->pc;
	live_nb = take_live_nb(arena->board, pos + 1);

	// if (live_nb == (*((int *)(pc->reg[0]))))
		// player->live_counter++;
	search_nb(data->players, data->n_players, live_nb, data->nb_cycles);
	pc->live++;
	pc->pc = (pc->pc + 1 + 4) % MEM_SIZE;//live + 4
}
