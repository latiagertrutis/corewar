/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:25:48 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/28 21:29:57 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static 	short charge_short(t_board *board, unsigned short pc_pos)
{
	int 	i;
	char	param[2];

	i = 0;
	while(i < 2)
	{
		param[2 - 1 - i] = board[(pc_pos + i) % MEM_SIZE].mem;
		i++;
	}
	// print_memory(param, 2, 2, 1);
//	exit(1);
	return (*((short *)param));
}

void		core_lfork(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short 	pc_i;
	unsigned short	pos;
	short			new_i;

	pos = pc->pc;
	new_i = charge_short(arena->board, pos + 1);
	// if (!(player->nb_pc % 20))
	if (!(data->nb_pc % 20))
	{
		// pc_i = (pc - player->pc);
		pc_i = (pc - data->pc);
		// player->pc = realloc_pc(player, player->pc, player->nb_pc);
		// player->pc = realloc_pc(data->pc, data->nb_pc);
		data->pc = realloc_pc(data->pc, data->nb_pc);

		pc = data->pc + pc_i; //pc * esta apuntando al ultimo pc creado
	}
	// player->pc[player->nb_pc] = (t_pc){pc->carry, ft_mod((pos + (new_i % IDX_MOD)), MEM_SIZE), 0, {{0}}};
	data->pc[data->nb_pc] = (t_pc){pc->carry, ft_mod((pos + (new_i)), MEM_SIZE), 0, {{0}}, pc->id, 0x1, 0x0};
	// ft_printf("pc1 es: %d\npc2 es: %d\nnb_pc es: %d\n", pc->pc, player->pc[player->nb_pc].pc, player->nb_pc);
//	exit(1);
	for (int j = 0; j < REG_NUMBER; j++) //PODEMOS USAR FOR ???????
	{
		// ft_memcpy(player->pc[player->nb_pc].reg[j], pc->reg[j], REG_SIZE);
		ft_memcpy(data->pc[data->nb_pc].reg[j], pc->reg[j], REG_SIZE);
	}
	pc->pc = (pc->pc + 3) % MEM_SIZE;
	// player->nb_pc++;
	data->nb_pc++;
}
