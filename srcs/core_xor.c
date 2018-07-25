/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:38:51 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/21 13:53:30 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				core_xor(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	arg1 = (t_arg){0, 0, 0, 0x1, {0}};
	arg2 = (t_arg){1, 0, 0, 0x1, {0}};
	get_arg(ocp, pc->pc, arena->board, &arg1);
	get_arg(ocp, pc->pc, arena->board, &arg2);
	if (!arg1.len || !arg2.len)
	{
		pc->pc = (pc->pc + 1) % MEM_SIZE;
		return ;
	}
	reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len) % IDX_MOD)) % MEM_SIZE].mem - 1;
	get_arg_value(arena->board, &arg1, pc);
	get_arg_value(arena->board, &arg2, pc);
//	ft_printf("arg1.len: %u\narg1.type: %u\n", arg1.len, arg1.type);
//	print_memory(arg1.arg, 4, 4, 1);
//	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
//	print_memory(arg2.arg, 4, 4, 1);
	*((uint32_t *)(pc->reg[reg_pos])) = *((uint32_t *)(arg1.arg)) ^ *((uint32_t *)(arg2.arg));
//	ft_printf("res en %u es: \n", reg_pos);
//	print_memory(pc->reg[reg_pos], 4, 4, 1);
	pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + 1) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
