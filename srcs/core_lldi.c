/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:56:52 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/22 13:52:30 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	core_lldi(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	arg1 = (t_arg){0, 0, 0, 0x0, {0}};
	arg2 = (t_arg){1, 0, 0, 0x0, {0}};
	get_arg(ocp, pc->pc, arena->board, &arg1);
	get_arg(ocp, pc->pc, arena->board, &arg2);
//	arg1.arg[0] = 0;
//	arg1.arg[1] = 1;
//	ft_printf("arg1:\n");
//	print_memory(arg1.arg, 4, 4, 1);
//	ft_printf("arg2: [%u]\n", arg2.len);
//	print_memory(arg2.arg, 4, 4, 1);
	if (!arg1.len || !arg2.len || arg2.type == IND_CODE)
	{
		pc->pc = (pc->pc + 1) % MEM_SIZE;
		return ;
	}
	reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len))) % MEM_SIZE].mem - 1;
	get_arg_value(arena->board, &arg1, pc);
	get_arg_value(arena->board, &arg2, pc);
	invert_bytes(arg1.arg, arg1.type == DIR_CODE ? 2 : 4);//apnar pa registro
	invert_bytes(arg2.arg, arg2.type == DIR_CODE ? 2 : 4);
	if (arg1.type == DIR_CODE)
		*((int *)arg1.arg) = *((short *)arg1.arg);
	if (arg2.type == DIR_CODE)
		*((int *)arg2.arg) = *((short *)arg2.arg);
//	ft_printf("arg1.len: %u\narg1.type: %u\n", arg1.len, arg1.type);
//	print_memory(arg1.arg, 4, 4, 1);
//	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
//	print_memory(arg2.arg, 4, 4, 1);
//	ft_printf("fsgdfg: %d\n", (0x00020002 + 2) % IDX_MOD );
//	exit(1);
	while (i < REG_SIZE)
	{
		pc->reg[reg_pos][i] = arena->board[ft_mod((pc->pc + i + ((*((int *)(arg1.arg)) + *((int *)(arg2.arg))))), MEM_SIZE)].mem;
		i++;
	}
	pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + 1) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
