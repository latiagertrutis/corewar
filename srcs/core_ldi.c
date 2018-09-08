/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:55:06 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/08 22:53:43 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			verify_ocp(const unsigned char ocp)
{
	if ((0xC0 & ocp) == 0xC0 || (0x30 & ocp) == 0x30 || (0xC & ocp) == 0x8 || (0xC & ocp) == 0xC || (0xC0 & ocp) == 0x0 || (0x30 & ocp) == 0x0 || (0xC & ocp) == 0x0)
		return (0);
	return (1);
}

void	core_ldi(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	if (verify_ocp(ocp))
	{
		arg1 = (t_arg){0, 0, 0, 0x0, {0}};
		arg2 = (t_arg){1, 0, 0, 0x0, {0}};
		get_arg(ocp, pc->pc, arena->board, &arg1);
		get_arg(ocp, pc->pc, arena->board, &arg2);
		reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len) % IDX_MOD)) % MEM_SIZE].mem - 1;
		if (get_arg_value(arena->board, &arg1, pc) && get_arg_value(arena->board, &arg2, pc))
		{
			invert_bytes(arg1.arg, arg1.type == DIR_CODE ? IND_SIZE : REG_SIZE);
			invert_bytes(arg2.arg, arg2.type == DIR_CODE ? IND_SIZE : REG_SIZE);
			// el problema aqui era que hay que sumar dos numeros y puede que esos numeros sean de 2 o 4 bytes
			// por tanto hay que coger el mayor size de los dos y dado que esta en complemento a2 si el numero es
			// negativo y es un short hay que castearlo a int para que se complete correctamente el resto de
			// los bytes
			if (arg1.type == DIR_CODE)
				*((REG_CAST *)arg1.arg) = *((IND_CAST *)arg1.arg);
			if (arg2.type == DIR_CODE)
				*((REG_CAST *)arg2.arg) = *((IND_CAST *)arg2.arg);
			while (i < REG_SIZE)
			{
				pc->reg[reg_pos][i] = arena->board[ft_mod((pc->pc + i + ((*((REG_CAST *)(arg1.arg)) + *((REG_CAST *)(arg2.arg))) % IDX_MOD)), MEM_SIZE)].mem;
				i++;
			}
		}
		pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + get_size_arg(ocp, 2, 0)) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
	}
	else
		pc->pc = (pc->pc + 1 + 1 + get_size_arg(ocp, 0, 0) + get_size_arg(ocp, 1, 0) + get_size_arg(ocp, 2, 0)) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
/* ft_printf("arg1:\n"); */
/* print_memory(arg1.arg, 4, 4, 1); */
/* ft_printf("arg2: [%u]\n", arg2.len); */
/* print_memory(arg2.arg, 4, 4, 1); */
/* ft_printf("************ LDI *****************\narg1 tipo %d cont: \n", arg1.type); */
/* print_memory(arg1.arg, 4, 4, 1); */
/* ft_printf("arg2 tipo: %u cont:\n", arg2.type); */
/* print_memory(arg2.arg, 4, 4, 1); */
/* ft_printf("**********************************\n"); */
