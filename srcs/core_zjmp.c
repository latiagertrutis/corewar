/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 05:25:36 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/15 05:25:37 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static 	int charge_short(int size, t_arena *arena, int pc_pos)
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

void	core_zjmp(t_player *player, t_op op, t_arena *arena)
{
	unsigned short index;

	player->carry = 1;
	if (player->carry == 1)
	{
		index = charge_short(2, arena, player->pc + 1);
		player->pc += ((short)index % IDX_MOD) % MEM_SIZE;
	}
}
