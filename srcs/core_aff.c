/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:44:28 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/25 14:49:35 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int to_big_endian(char *reg)
{
	int 	i;
	char	param[4];

	i = 0;
	while (i < 4)
	{
		param[3 - i] = reg[i];
		i++;
	}
	return (*((unsigned int *)param));
}

void		core_aff(t_pc *pc, t_arena *arena, t_data *data)
{
	char 			reg_nb;
	char 			reg_content;

	// ft_printf("JOPUTA");
//	exit(1);
	reg_nb = arena->board[(pc->pc + 2) % MEM_SIZE].mem;
	reg_content = (to_big_endian(pc->reg[reg_nb - 1])) % 256;
	// ft_putstr("Aff: ");
	// ft_putchar(reg_content);
	// ft_putchar('\n');
	pc->pc = ((pc->pc + 3) % MEM_SIZE);
}


