/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/16 19:03:33 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_board_to_screen(t_sdl *Graph, t_arena *arena, int first_time)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (arena->board[i].mem != arena->lst_board[i].mem || first_time)
		{
			ft_write_byte(i, arena->board[i], Graph);
			arena->lst_board[i].mem = arena->board[i].mem;
			arena->lst_board[i].id = arena->board[i].id;
		}
		i++;
	}
	SDL_UpdateWindowSurface(Graph->screen.window);
}
