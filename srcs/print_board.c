/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 23:21:36 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/10 00:28:36 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_board(t_data *data, t_board *board)
{
	size_t			i;
	int 			j;
	char 			*hexa;

	hexa = "0123456789abcdef";
	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64 && i + j < MEM_SIZE)
		{
			ft_putstr(data->palete[(int)board[i + j].id]);
			ft_putchar(hexa[board[i + j].mem / 16]); //%16?
			ft_putchar(hexa[board[i + j].mem % 16]);
			ft_putchar(' ');
//			ft_putstr("\033[0m ");
			j++;
		}
		ft_putchar('\n');
		i += 64;
	}
}