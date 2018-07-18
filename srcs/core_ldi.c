/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:55:06 by mrodrigu          #+#    #+#             */
//   Updated: 2018/07/17 17:36:05 by mrodrigu         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	core_ldi(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	arg1 = get_arg(ocp, pc->pc, arena->board, 0);
	arg2 = get_arg(ocp, pc->pc, arena->board, 1);
	if (!arg1.len || !arg2.len || arg2.type == IND_CODE)
	{
		pc->pc = (pc->pc + 1) % MEM_SIZE;
		return ;
	}
	reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len) % IDX_MOD)) % MEM_SIZE].mem - 1;
	get_arg_value(arena->board, &arg1, pc);
	get_arg_value(arena->board, &arg2, pc);
	ft_printf("arg1.len: %u\narg1.type: %u\n", arg1.len, arg1.type);
	print_memory(arg1.arg, 4, 4, 1);
	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
	print_memory(arg2.arg, 4, 4, 1);
	while (i < REG_SIZE)
	{
		pc->reg[reg_pos][i] = arena->board[(pc->pc + ((*((uint32_t *)(arg1.arg)) + *((uint32_t *)(arg2.arg)) + i) % IDX_MOD)) % MEM_SIZE].mem;
		i++;
	}
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
	pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + 1);//and + ocp + arg1 + arg2 + rg
}
