/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:16:28 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/17 17:45:40 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arg		get_arg(const unsigned char ocp, unsigned short pos, t_board *board, const unsigned char n_arg)
{
	t_arg			arg;
	unsigned int	i;
	unsigned char	sum;

	i = 0;
	sum = 0;
	arg.n_arg = n_arg;
	if (!(arg.len = get_size_arg(ocp, n_arg)))
		return (arg);
	arg.type = (ocp & (0xC0 >> (2 * n_arg))) >> (2 * (3 - n_arg));
	while (i < n_arg)
		sum += get_size_arg(ocp, i++);
	i = 0;
	while (i < arg.len && i < MAX_ARG_LEN)
	{
		arg.arg[i] = board[(pos + ((2 + sum + i) % IDX_MOD)) % MEM_SIZE].mem;
		i++;
	}
	return (arg);
}
