/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:39:59 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/21 13:59:24 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		add_reg(t_pc *pc, const unsigned char reg1, const unsigned char reg2, const unsigned char reg3)
{
	(*(unsigned int *)pc->reg[reg3]) = (*(unsigned int *)pc->reg[reg1]) - (*(unsigned int *)pc->reg[reg2]);
	ft_printf("el reg vale %u\n", (*(unsigned int *)pc->reg[reg3]));
	pc->pc = (pc->pc + 1 + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2 + reg3
}

void			core_sub(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	if (ocp == 0x54 && (reg1 = arena->board[(pos + 2) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg2 = arena->board[(pos + 3) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg3 = arena->board[(pos + 4) % MEM_SIZE].mem - 1) < REG_NUMBER)
		add_reg(pc, reg1, reg2, reg3);
	else
		pc->pc  = (pc->pc + 1) % MEM_SIZE;
}
