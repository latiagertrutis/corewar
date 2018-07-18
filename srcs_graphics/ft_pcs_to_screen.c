/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/17 09:47:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Color	take_color_pc(int id)
{
	int mod;

	mod = 5;
	if (!id)
		return ((SDL_Color){51 - mod, 255 - mod, 51 - mod, SDL_ALPHA_OPAQUE});
	else if (id == 1)
		return ((SDL_Color){255 - mod, 204 - mod, 0, SDL_ALPHA_OPAQUE});
	else if (id == 2)
		return ((SDL_Color){0xFF - mod, 0xF2 - mod, 0xCF - mod, SDL_ALPHA_OPAQUE});
	else if (id == 3)
		return ((SDL_Color){252 - mod, 102 - mod, 92 - mod, SDL_ALPHA_OPAQUE});
	else
		return ((SDL_Color){89 - mod, 89 - mod, 75 - mod, SDL_ALPHA_OPAQUE});
}

void	ft_pcs_to_screen(t_sdl *Graph, t_player *players, int n_players, t_board board[MEM_SIZE])
{
	int i;
	SDL_Color color;
	SDL_Surface *screen;
	SDL_Rect	pc;
	SDL_Texture *text;
	

	i = 0;
	if (!(screen = SDL_CreateRGBSurface(0, Graph->screen.w, Graph->screen.h, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK)))
		ft_SDL_error("SDL_CreateRGBSurface", MODE_SDL);
//	SDL_SetColorKey(screen, SDL_FALSE, 0x3d3d33);
//	screen = Graph->screen.screen;
	while (i < n_players)
	{
		if (!players[i].wait_cycles)
		{
			if (players[i].lst2_pc >= 0)
				ft_write_byte(players[i].lst2_pc, board[players[i].lst2_pc], Graph);
			players[i].lst2_pc = players[i].lst_pc;
			players[i].lst_pc = players[i].pc;
			color = take_color_pc(players[i].id);
			SDL_SetRenderDrawColor(Graph->screen.Renderer, color.r, color.g,
				color.b, color.a);
			pc = (SDL_Rect){Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1) * (players[i].pc % Graph->cuant_squares[0]) + 1, Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1) * (players[i].pc / Graph->cuant_squares[1]) + 1, Graph->square->w - 2, Graph->square->h - 2};
			SDL_FillRect(screen, &pc, SDL_MapRGBA(screen->format, color.r, color.g, color.b, color.a));
//			players[i].lst2_pc = players[i].lst_pc;
//			players[i].lst_pc = players[i].pc;
			if (players[i].pc == 64 * 50)
				exit(1);
		}
		i++;
	}
	text = SDL_CreateTextureFromSurface(Graph->screen.Renderer, screen);
	SDL_RenderCopy(Graph->screen.Renderer, text, NULL, NULL);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(text);
//	SDL_RenderPresent(Graph->screen.Renderer);
//	SDL_RenderPresent(Graph->screen.Renderer);
//	usleep(100000000);
//	exit(1);
//	SDL_UpdateWindowSurface(Graph->screen.window);
}
