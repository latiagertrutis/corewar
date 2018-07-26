/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:39:59 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/26 21:45:03 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		sub_reg(t_pc *pc, const unsigned char reg1, const unsigned char reg2, const unsigned char reg3)
{
	char aux1[REG_SIZE];
	char aux2[REG_SIZE];
	unsigned char i;

	i = 0;
	while (i < REG_SIZE)
	{
		aux1[REG_SIZE - 1 - i] = pc->reg[reg1][i];
		aux2[REG_SIZE - 1 - i] = pc->reg[reg2][i];
		i++;
	}
//	ft_printf("RESTA el reg1: %u vale: %d\n", reg1, *((int *)aux1));
//	print_memory(pc->reg[reg1], 4, 4, 1);
//	ft_printf("SUMA el reg2: %u vale: %d\n", reg2, *((int *)aux2));
//	print_memory(pc->reg[reg2], 4, 4, 1);
	(*(int32_t *)pc->reg[reg3]) = *((int32_t *)aux1) - *((int32_t *)aux2);
//	ft_printf("SUMA el reg3: %u vale: %d\n", reg3, *((int *)pc->reg[reg3]));
	invert_bytes(pc->reg[reg3], REG_SIZE);
//	print_memory(pc->reg[reg3], 4, 4, 1);
	pc->pc = (pc->pc + 1 + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2 + reg3
	pc->carry = (!*((int *)(pc->reg[reg3]))) ? 0x1 : 0x0;//actualizar carry
}

void			core_sub(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//pc + 1 = ocp, pc + 2 = first arg
	if (ocp == 0x54 && (reg1 = arena->board[(pos + 2) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg2 = arena->board[(pos + 3) % MEM_SIZE].mem - 1) < REG_NUMBER && (reg3 = arena->board[(pos + 4) % MEM_SIZE].mem - 1) < REG_NUMBER)
		sub_reg(pc, reg1, reg2, reg3);
	else if (!check_ocp(ocp))
		pc->pc = (pc->pc + 2) % MEM_SIZE;
	else
		pc->pc = (pc->pc + 1 + get_size_arg(ocp, 0, 4) + get_size_arg(ocp, 1, 4) + get_size_arg(ocp, 2, 4)) % MEM_SIZE;
}
