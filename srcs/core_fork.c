/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 09:34:50 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/15 09:34:53 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	fork_player(t_player *player)
{
	
}

static int 	charge_short(int size, t_arena *arena, int pc_pos)
{
	int 	i;
	char	param[size];

	i = 0;
	while(i < size)
	{
		param[size - 1 - i] = arena->board[(pc_pos + i) % MEM_SIZE].mem;
		i++;
	}
	print_memory(param, size, size, 1);
	return (*((unsigned short *)param));
}

void		core_fork(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned int pc_i;

	new_pc = charge_short(2, arena, ((pc->pc) + 1 % MEM_SIZE));
	if (!(player->nb_pc % 20))
	{
		pc_i = (pc - player->pc);
		player->pc = realloc_pc(player, player->pc, player->nb_pc);
		pc = player->pc + i;
	}
	player->nb_pc++;
	
	fork_player(player);
}
