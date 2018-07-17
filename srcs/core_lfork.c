/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:25:48 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 16:25:50 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void		core_lfork(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned short 	pc_i;
	short			new_i;

	new_i = (short)charge_short(2, arena, ((pc->pc) + 1 % MEM_SIZE));
	if (!(player->nb_pc % 20))
	{
		pc_i = (pc - player->pc);
		player->pc = realloc_pc(player, player->pc, player->nb_pc);
		pc = player->pc + pc_i;
	}
	player->pc[player->nb_pc] = (t_pc){(pc->pc + new_i) % MEM_SIZE, pc->carry, 0, {{0}}};
	ft_memcpy((player->pc + player->nb_pc)->reg, pc->reg, REG_NUMBER * REG_SIZE);
	pc->pc += 3 % MEM_SIZE;
	player->nb_pc++;
}
