/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 18:30:40 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/25 19:53:25 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"
#include "graphics.h"

void	new_frame(void)
{
	unsigned int i;

	if (!g_aux)
	{
		if (!(g_aux = (t_graphics *)malloc(sizeof(t_graphics))))
			ft_error("malloc failed in new_frame");
		i = 0;
		if (g_graph_tail)
		{
			while (i < MEM_SIZE)
			{
				g_aux->board[i] = (t_board){g_mem[i], g_graph_tail->board[i].new ? g_graph_tail->board[i].new - 1 : 0, g_graph_tail->board[i].id};
				i++;
			}
		}
		else
		{
			while (i < MEM_SIZE)
			{
				g_aux->board[i] = (t_board){g_mem[i], 0, 0};
				i++;
			}
		}
		g_aux->prog_end = 0x0;
		g_aux->next = NULL;
	}
}
