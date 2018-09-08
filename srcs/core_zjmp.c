/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 05:25:36 by mzabalza          #+#    #+#             */
/*   Updated: 2018/09/08 22:00:13 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static 	short charge_short(t_board *board, unsigned short pc_pos)
{
	int 	i;
	char	param[IND_SIZE];

	i = 0;
	while(i < IND_SIZE)
	{
		param[IND_SIZE - 1 - i] = board[(pc_pos + i) % MEM_SIZE].mem;
		i++;
	}
	// print_memory(param, 2, 2, 1);
//	exit(1);
	return (*((IND_CAST *)param));
}

void	core_zjmp(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short pos;

//	 pc->carry = 1;
	if (pc->carry == 0x1)
	{
		pos = pc->pc;
		pc->pc = ft_mod(pc->pc + (charge_short(arena->board, pos + 1) % IDX_MOD), MEM_SIZE);
	}
	else
		pc->pc = (pc->pc + 1 + IND_SIZE) % MEM_SIZE;//zjmp + D2
}
