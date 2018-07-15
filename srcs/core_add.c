/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 05:45:24 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/14 06:44:49 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		add_reg(t_player *player, const unsigned char reg1, const unsigned char reg2, const unsigned char reg3)
{
	(*(unsigned int *)player->reg[reg3]) = (*(unsigned int *)player->reg[reg1]) + (*(unsigned int *)player->reg[reg2]);
	ft_printf("el reg vale %u\n", (*(unsigned int *)player->reg[reg3]));
	*(player->pc) = (*(player->pc) + 1 + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2 + reg3
	player->carry = (!*((int *)(player->reg[reg3]))) ? 0x1 : 0x0;//actualizar carry
}

void			core_add(t_player *player, unsigned short *pc, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;

	pos = *(player->pc);
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	if (ocp == 0x54 && (reg1 = arena->board[(pos + 2) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg2 = arena->board[(pos + 3) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg3 = arena->board[(pos + 4) % MEM_SIZE].mem - 1) < REG_NUMBER)
		add_reg(player, reg1, reg2, reg3);
}
