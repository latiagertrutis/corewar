/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mem_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 04:32:58 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/13 04:39:29 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*get_mem_board(t_board *board, const unsigned int size)
{
	unsigned char	*buff;
	unsigned int	i;

	if (!(buff = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		ft_error("malloc failed");
	i = 0;
	while (i < size)
	{
		buff[i] = board[i].mem;
		i++;
	}
	return (buff);
}
