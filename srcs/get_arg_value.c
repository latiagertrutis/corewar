/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:17:57 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/08 21:27:16 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_arg_value(t_board *board, t_arg *arg, t_pc *pc)
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
			arg->arg[i] = board[ft_mod((pc->pc + ((i + *((IND_CAST *)aux)) % IDX_MOD)), MEM_SIZE)].mem;
			i++;
		}
	}
	return (1);
}
