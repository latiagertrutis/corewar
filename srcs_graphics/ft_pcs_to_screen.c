/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/15 15:43:18 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Color	take_color(int id)
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

void	ft_pcs_to_screen(t_sdl *Graph, t_player *players, int n_players)
{
	int i;
	SDL_Color color;
	SDL_Color back_color;

	i = 0;
	while (i < n_players)
	{
//		if (!players[i].wait_cycles)
//		{
			SDL_GetRenderDrawColor(Graph->screen.Renderer, &back_color.r, &back_color.g, &back_color.b, &back_color.a);
			color = take_color(players[i].id);
			SDL_SetRenderDrawColor(Graph->screen.Renderer, color.r, color.g, color.b, color.a);
			Graph->square->x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1) * (players[i].pc % Graph->cuant_squares[0]) + 1;
			Graph->square->y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1) * (players[i].pc / Graph->cuant_squares[1]) + 1;
			if (SDL_RenderFillRect(Graph->screen.Renderer, &(SDL_Rect){Graph->square->x, Graph->square->y, Graph->square->w - 2, Graph->square->h - 2}))
				ft_SDL_error("SDL_RenderFillRect", MODE_SDL);
			SDL_SetRenderDrawColor(Graph->screen.Renderer, back_color.r, back_color.g, back_color.b, back_color.a);
//		}
		i++;
	}
	SDL_RenderPresent(Graph->screen.Renderer);
}
