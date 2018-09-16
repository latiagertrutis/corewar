/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:44:28 by mzabalza          #+#    #+#             */
/*   Updated: 2018/09/16 13:41:00 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			verify_ocp(const unsigned char ocp)
{
	if ((0xC0 & ocp) == 0x80 || (0xC0 & ocp) == 0xC0 || (0xC0 & ocp) == 0x0)
		return (0);
	return (1);
}

static void print_reg(t_pc *pc, unsigned char reg_nb)
{
	/* unsigned int	 i; */
	REG_CAST	aux_reg;

	/* i = 0; */
	/* while (i < REG_SIZE) */
	/* { */
	/* 	aux_reg[REG_SIZE - 1 - i] = pc->reg[reg_nb][i]; */
	/* 	i++; */
	/* } */
	aux_reg = *((REG_CAST *)pc->reg[reg_nb]);
	invert_bytes(&aux_reg, REG_SIZE);
	ft_putstr("Aff: ");
	ft_putchar(aux_reg);
	ft_putchar('\n');
}

void		core_aff(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	unsigned char	reg_nb;

	// ft_printf("JOPUTA");
//	exit(1);
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	if (verify_ocp(ocp))
	{
		if ((reg_nb = arena->board[(pc->pc + 2) % MEM_SIZE].mem - 1) < REG_NUMBER && reg_nb >= 0)
			print_reg(pc, reg_nb);
		pc->pc = ((pc->pc + 1 + 1 + 1) % MEM_SIZE);//aff + ocp + rg
	}
	else
		pc->pc = ((pc->pc + 1 + 1 + get_size_arg(ocp, 0, 1)) % MEM_SIZE);//aff + ocp + rg
}


