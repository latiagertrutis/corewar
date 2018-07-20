/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:16:28 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/19 14:04:02 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		get_arg(const unsigned char ocp, unsigned short pos, t_board *board, t_arg *arg)
{
	unsigned int	i;
	unsigned char	sum;

	i = 0;
	sum = 0;
	if (!(arg->len = get_size_arg(ocp, arg->n_arg, arg->dir_size)))
		return ;
	arg->type = (ocp & (0xC0 >> (2 * arg->n_arg))) >> (2 * (3 - arg->n_arg));
	while (i < arg->n_arg)
		sum += get_size_arg(ocp, i++, arg->dir_size);
	i = 0;
	ft_memset(arg->arg, 0, MAX_ARG_LEN);
	while (i < arg->len && i < MAX_ARG_LEN)
	{
		arg->arg[i] = board[(pos + ((2 + sum + i) % IDX_MOD)) % MEM_SIZE].mem;
		i++;
	}
}
