/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/20 12:51:22 by jagarcia         ###   ########.fr       */
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

void	ft_pcs_to_screen(t_data *data, t_sdl *Graph, t_player *players)
{
	unsigned int i;
	unsigned int j;
	SDL_Color color;
	SDL_Rect	pc_rect;
	

	i = 0;
	while (i < data->n_players)
	{
		j = 0;
		color = take_color_pc(players[i].id);
		if (SDL_SetRenderDrawColor(Graph->screen.Renderer, color.r, color.g, color.b , SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
		while (j < players[i].nb_pc)
		{
			pc_rect = (SDL_Rect){Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1) * (players[i].pc[j].pc % Graph->cuant_squares[0]) + 1, Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1) * (players[i].pc[j].pc / Graph->cuant_squares[1]) + 1, Graph->square->w - 2, Graph->square->h - 2};
//			if (players[i].pc[j].pc == 64)
//				exit(1);
			if (SDL_FillRect(Graph->screen.screen, &pc_rect, (color.r << 24) | color.g << 16 | color.b << 8 | color.a))
				ft_SDL_error("SDL_FillRect", MODE_SDL);
				
			j++;
		}
		i++;
	}
}
