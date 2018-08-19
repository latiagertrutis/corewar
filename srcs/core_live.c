/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:50:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/08/18 17:40:13 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void search_nb(t_player *players, int nb_players, int live_nb, int nb_cycles)
{
	int i;

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
	live_nb = take_live_nb((arena->board) + pos + 1);

	// if (live_nb == (*((int *)(pc->reg[0]))))
		// player->live_counter++;
	search_nb(data->players, data->n_players, live_nb, data->nb_cycles);
	pc->live++;
	pc->pc = (pc->pc + 1 + DIR_SIZE) % MEM_SIZE;//live + dir
}
