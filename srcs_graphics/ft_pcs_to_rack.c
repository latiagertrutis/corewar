/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/25 17:50:11 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static Uint32	take_color_pc(int id, SDL_PixelFormat *format, int alpha_mod)
{
	int mod;

	mod = 5;
	if (!id)
		return (SDL_MapRGBA(format, 51, 255, 51, 255 - alpha_mod));
	else if (id == 1)
		return (SDL_MapRGBA(format, 255, 204, 0, 255 - alpha_mod));
	else if (id == 2)
		return (SDL_MapRGBA(format, 0xFF, 0xF2, 0xCF, 255 - alpha_mod));
	else if (id == 3)
		return (SDL_MapRGBA(format, 252, 102, 92, 255 - alpha_mod));
	else
		return (SDL_MapRGBA(format, 89, 89, 75, 255 - alpha_mod));
}

void	ft_pcs_to_rack(unsigned int n_players, t_sdl *Graph, t_player *players, int alpha_mod)
{
	unsigned int i;
	unsigned int j;
	Uint32  color;
	SDL_Rect	pc_rect;
	int		*pixel;
	int		pitch;
	
	i = 0;
	while (i < n_players)
	{
		j = 0;
		color = take_color_pc(players[i].id, Graph->rack->format, alpha_mod);
		while (j < players[i].nb_pc)
		{
			/* pc_rect = (SDL_Rect){(Graph->square->w - 1) * */
			/* 	(players[i].pc[j].pc % Graph->cuant_squares[0]) + 1, */
			/* 	(Graph->square->h - 1) * (players[i].pc[j].pc / */
			/* 	Graph->cuant_squares[1]) + 1, Graph->square->w - 2, */
			/* 	Graph->square->h - 2}; */
			pc_rect = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
			SDL_LockTexture(Graph->pc, &pc_rect, (void **)&pixel, &pitch);
			for(int d = 0; d < pc_rect.h; d++)
			{
				for(int k = 0; k < pc_rect.w; k++)
					pixel[d * pitch / 4 + k] = color;
			}
			SDL_UnlockTexture(Graph->pc);
			pc_rect.x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1) * (players[i].pc[j].pc % Graph->cuant_squares[0]) + 1;
			pc_rect.y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1) * (players[i].pc[j].pc / Graph->cuant_squares[1]) + 1;
			SDL_RenderCopy(Graph->screen.Renderer, Graph->pc, NULL, &pc_rect);
			
			j++;
			
		}
		i++;
	}
}
