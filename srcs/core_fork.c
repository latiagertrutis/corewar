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

void		core_fork(t_player *player, t_op op, t_arena *arena)
{
	unsigned short new_pc;

	new_pc = charge_short(2, arena, player->pc + 1);
	fork_player(player);


}
