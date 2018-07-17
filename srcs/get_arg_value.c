/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:17:57 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/17 17:19:14 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			get_arg_value(t_board *board, t_arg *arg, t_pc *pc)
{
	unsigned char	aux[MAX_ARG_LEN];
	unsigned char	i;

	i = 0;
	if (arg->type == REG_CODE)
	{
		aux[0] = arg->arg[0];
		while (i < REG_SIZE)
		{
			arg->arg[i] = pc->reg[aux[0] - 1][i];
			i++;
		}
	}
	else if (arg->type == IND_CODE)
	{
		aux[1] = arg->arg[0];
		aux[0] = arg->arg[1];
		while (i < REG_SIZE)
		{
			arg->arg[i] = board[(pc->pc + ((i + *((unsigned short *)aux)) % IDX_MOD)) % MEM_SIZE].mem;
			i++;
		}
	}
}
