/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:38:01 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/28 17:14:06 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			verify_ocp(const unsigned char ocp)
{
	if ((0xC & ocp) == 0x8 || (0xC & ocp) == 0xC)
		return (0);
	return (1);
}

static void			apply_or(t_arg *arg1, t_arg *arg2, t_pc *pc, const unsigned char reg_pos)
{
	unsigned int i;

	if (MAX_ARG_LEN == 4)
		*((int32_t *)(pc->reg[reg_pos])) = *((int32_t *)(arg1->arg)) | *((int32_t *)(arg2->arg));
	else
	{
		i = 0;
		while (i < MAX_ARG_LEN)
		{
			pc->reg[reg_pos][i] = arg1->arg[i] | arg2->arg[i];
			i++;
		}
	}
}

void				core_or(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;

	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//pc + 1 = ocp, pc + 2 = first arg
	if (verify_ocp(ocp))
	{
		arg1 = (t_arg){0, 0, 0, 0x1, {0}};
		arg2 = (t_arg){1, 0, 0, 0x1, {0}};
		get_arg(ocp, pc->pc, arena->board, &arg1);
		get_arg(ocp, pc->pc, arena->board, &arg2);
		reg_pos = arena->board[(pc->pc + 2 + arg1.len + arg2.len) % MEM_SIZE].mem - 1;
		if (get_arg_value(arena->board, &arg1, pc) && get_arg_value(arena->board, &arg2, pc))
		{
			apply_or(&arg1, &arg2, pc, reg_pos);
			pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
		}
		pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + 1) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
	}
	else
		pc->pc = (pc->pc + 1 + 1 + get_size_arg(ocp, 0, 1) + get_size_arg(ocp, 1, 1) + get_size_arg(ocp, 2, 1)) % MEM_SIZE;//and + ocp + arg1 + arg2 + arg3
}
//		ft_printf("arg1.len: %u\narg1.type: %u\n", arg1.len, arg1.type);
//		print_memory(arg1.arg, 4, 4, 1);
//		ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
//		print_memory(arg2.arg, 4, 4, 1);
//		ft_printf("res en %u es: \n", reg_pos);
//		print_memory(pc->reg[reg_pos], 4, 4, 1);
