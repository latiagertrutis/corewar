/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 09:34:50 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/21 18:34:12 by mrodrigu         ###   ########.fr       */
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

void		core_fork(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
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
	player->pc[player->nb_pc] = (t_pc){pc->carry, ft_mod((pc->pc + (new_i % IDX_MOD)), MEM_SIZE), 0, {{0}}};
	ft_printf("pc1 es: %d\npc2 es: %d\nnb_pc es: %d\n", pc->pc, player->pc[player->nb_pc].pc, player->nb_pc);
//	exit(1);
	for (int j = 0; j < REG_NUMBER; j++)
		ft_memcpy(player->pc[player->nb_pc].reg[j], pc->reg[j], REG_SIZE);
	pc->pc = (pc->pc + 3) % MEM_SIZE;
	player->nb_pc++;
}
