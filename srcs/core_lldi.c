/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:56:52 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/15 23:15:17 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_arg_value_2(t_board *board, t_arg *arg, t_pc *pc)
{
	unsigned char	aux[MAX_ARG_LEN];
	unsigned char	i;

	i = 0;
	if (arg->type == REG_CODE)
	{
		aux[0] = arg->arg[0];
		if (aux[0] > 16 || aux[0]<= 0)
			return (0);
		*((REG_CAST *)arg->arg) = *((REG_CAST *)pc->reg[aux[0] - 1]);
		/* while (i < REG_SIZE) */
		/* { */
		/* 	arg->arg[i] = pc->reg[aux[0] - 1][i]; */
		/* 	i++; */
		/* } */
	}
	else if (arg->type == IND_CODE)
	{
		/* aux[1] = arg->arg[0]; */
		/* aux[0] = arg->arg[1]; */
		*((IND_CAST *)aux) = *((IND_CAST *)arg->arg);
		invert_bytes(aux, IND_SIZE);
		while (i < REG_SIZE)
		{
			arg->arg[i] = board[ft_mod((pc->pc + ((i + *((IND_CAST *)aux)))), MEM_SIZE)].mem;
			i++;
		}
	}
	return (1);
}

static int			verify_ocp(const unsigned char ocp)
{
	if ((0xC0 & ocp) == 0xC0 || (0x30 & ocp) == 0x30 || (0xC & ocp) == 0x8 || (0xC & ocp) == 0xC || (0xC0 & ocp) == 0x0 || (0x30 & ocp) == 0x0 || (0xC & ocp) == 0x0)
		return (0);
	return (1);
}

void	core_lldi(t_pc *pc, t_arena *arena, t_data *data)
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
		reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len))) % MEM_SIZE].mem - 1;
		if (get_arg_value_2(arena->board, &arg1, pc) && get_arg_value_2(arena->board, &arg2, pc))
		{
			invert_bytes(arg1.arg, arg1.type == DIR_CODE ? IND_SIZE : REG_SIZE);//apnar pa registro
			invert_bytes(arg2.arg, arg2.type == DIR_CODE ? IND_SIZE : REG_SIZE);
			if (arg1.type == DIR_CODE)
				*((REG_CAST *)arg1.arg) = *((IND_CAST *)arg1.arg);
			if (arg2.type == DIR_CODE)
				*((REG_CAST *)arg2.arg) = *((IND_CAST *)arg2.arg);
			while (i < REG_SIZE)
			{
				pc->reg[reg_pos][i] = arena->board[ft_mod((pc->pc + i + ((*((int *)(arg1.arg)) + *((int *)(arg2.arg))))), MEM_SIZE)].mem;
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
