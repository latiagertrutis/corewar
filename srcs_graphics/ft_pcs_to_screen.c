/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/23 13:27:04 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static Uint32	take_color_pc(int id, SDL_PixelFormat *format)
{
	int mod;

	mod = 5;
	if (!id)
		return (SDL_MapRGBA(format, 51, 255, 51, 255));
	else if (id == 1)
		return (SDL_MapRGBA(format, 255, 204, 0, 255));
	else if (id == 2)
		return (SDL_MapRGBA(format, 0xFF, 0xF2, 0xCF, 255));
	else if (id == 3)
		return (SDL_MapRGBA(format, 252, 102, 92, 255));
	else
		return (SDL_MapRGBA(format, 89, 89, 75, 255));
}

void	ft_pcs_to_screen(t_data *data, t_sdl *Graph, t_player *players)
{
	unsigned int i;
	unsigned int j;
	Uint32  color;
	SDL_Rect	pc_rect;
	int		*pixel;
	int		pitch;
	

	i = 0;
	while (i < data->n_players)
	{
		j = 0;
		color = take_color_pc(players[i].id, Graph->screen.screen->format);
//		if (SDL_SetRenderDrawColor(Graph->screen.Renderer, color & 0xFF000000, color & 0xFF0000, color & 0xFF00 , color & 0xFF))
//			ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
		while (j < players[i].nb_pc)
		{
			pc_rect = (SDL_Rect){(Graph->square->w - 1) * (players[i].pc[j].pc % Graph->cuant_squares[0]) + 1, (Graph->square->h - 1) * (players[i].pc[j].pc / Graph->cuant_squares[1]) + 1, Graph->square->w - 2, Graph->square->h - 2};
//			if (players[i].pc[j].pc == 64)
//				exit(1);
//			if (SDL_FillRect(Graph->screen.screen, &pc_rect, color))
//			    ft_SDL_error("SDL_FillRect", MODE_SDL);
			SDL_LockTexture(Graph->screen.texture, &pc_rect, (void **)&pixel, &pitch);
			for(int d = 0; d < pc_rect.h; d++)
			{
				for(int k = 0; k < pc_rect.w; k++)
					pixel[d * pitch / 4 + k] = color;
			}
			SDL_UnlockTexture(Graph->screen.texture);

			j++;
		}
		i++;
	}
}
