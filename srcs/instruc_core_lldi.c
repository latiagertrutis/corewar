/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_core_lldi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 21:39:29 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/10/01 15:54:19 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

static char	verify_ocp(const unsigned char ocp)
{
	if ((0xC0 & ocp) == 0x0 ||
	    (0x30 & ocp) == 0x0 || (0x30 & ocp) == 0x30 ||
	    (0xC & ocp) == 0x0 || (0xC & ocp) == 0x8 || (0xC & ocp) == 0xC)
		return (0);
	return (1);
}

static void	load_indirect(const t_arg arg1, const t_arg arg2, const unsigned char reg_pos, t_pc *pc)
{
	int				inc;
	unsigned int	pos;
	unsigned char 	i;
	REG_CAST		value1;
	REG_CAST		value2;

	pos = pc->pc;
	value1 = *((REG_CAST *)(arg1.arg));
	value2 = *((REG_CAST *)(arg2.arg));
	inc = (pos + (value1 + value2));
	if ((inc + REG_SIZE) < MEM_SIZE && inc >= 0)
		*((REG_CAST *)(pc->reg[reg_pos])) = *((REG_CAST *)(g_mem + inc));
	else
	{
		i = 0;
		while (i < REG_SIZE)
		{
			pc->reg[reg_pos][i] = g_mem[ft_mod(inc + i, MEM_SIZE)];
			i++;
		}
	}
	if (value1 < 0)
	value1 = ft_mod(value1, MEM_SIZE);
	if (value2 < 0)
	value2 = ft_mod(value2, MEM_SIZE);
	inc = value1 + value2 + pos;
	ft_printf("P %4d | lldi %d %d r%d\n       | -> load from %d + %d = %d (with pc %d)\n",
	          pc->pc_num + 1, value1, value2, reg_pos + 1, value1, value2, value1 + value2, inc);
}

void		instruc_core_lldi(t_pc *pc)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned int	pos;

	pos = pc->pc;
	ocp = g_mem[(pos + 1) % MEM_SIZE];
	if (verify_ocp(ocp))
	{
		arg1 = (t_arg){0, 0, 0, 0x0, {0}};
		arg2 = (t_arg){1, 0, 0, 0x0, {0}};
		get_arg(ocp, pos, 0, &arg1);
		get_arg(ocp, pos, arg1.len, &arg2);
		reg_pos = g_mem[(pos + 1 + 1 + arg1.len + arg2.len) % MEM_SIZE] - 1;
		if (get_arg_value(&arg1, pc, 0) && get_arg_value(&arg2, pc, 0) && reg_pos < REG_NUMBER)
		{
			invert_bytes(arg1.arg, arg1.type == DIR_CODE ? IND_SIZE : REG_SIZE);
			invert_bytes(arg2.arg, arg2.type == DIR_CODE ? IND_SIZE : REG_SIZE);
			if (arg1.type == DIR_CODE)
				*((REG_CAST *)arg1.arg) = *((IND_CAST *)arg1.arg);
			if (arg2.type == DIR_CODE)
				*((REG_CAST *)arg2.arg) = *((IND_CAST *)arg2.arg);
			load_indirect(arg1, arg2, reg_pos, pc);
			pc->carry = (*((REG_CAST *)(pc->reg[reg_pos]))) ? 0x0 : 0x1;
		}
		pc->pc = (pos + 1 + 1 + arg1.len + arg2.len + 1) % MEM_SIZE;
	}
	else
		pc->pc = (pos + 1 + 1 + get_size_arg(ocp, 0, 0) + get_size_arg(ocp, 1, 0) + get_size_arg(ocp, 2, 0)) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
