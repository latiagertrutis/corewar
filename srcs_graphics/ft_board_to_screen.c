/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/18 09:26:26 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_board_to_screen(t_sdl *Graph, t_arena *arena)
{
	int			i;
//	SDL_Texture *text;
	int			flag;

	i = 0;
	flag = 0;
	if (SDL_FillRect(Graph->screen.screen, &(SDL_Rect){0, 0, Graph->screen.w, Graph->screen.h}, 0))
		ft_SDL_error("SDL_FillRect", MODE_SDL);
	while (i < MEM_SIZE)
	{
//		if (arena->board[i].mem != arena->lst_board[i].mem || first_time)
//		{
			ft_write_byte(i, arena->board[i], Graph);
//			arena->lst_board[i].mem = arena->board[i].mem;
//			arena->lst_board[i].id = arena->board[i].id;
//			flag = 1;
//		}
		i++;
	}
//	if (flag)
//	{
//	text = SDL_CreateTextureFromSurface(Graph->screen.Renderer, Graph->screen.screen);
//	SDL_RenderCopy(Graph->screen.Renderer, text, NULL, NULL);
//	SDL_DestroyTexture(text);
//	}
//	SDL_RenderPresent(Graph->screen.Renderer);
//	SDL_UpdateWindowSurface(Graph->screen.window);
}
