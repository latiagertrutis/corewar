/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_back_to_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:19:40 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/05 17:42:34 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int	put_end_frame(void)
{
	int			i;
	SDL_Rect	pos;
	
	i = -1;

	pos = (SDL_Rect){g_graph->info_marc->x, g_graph->square_info->h +
		g_graph->screen.h * UPPER_BORDER, g_graph->info_marc->w -
		(g_graph->square_info->w - g_graph->player_nbr->w * 21),
		g_graph->info_marc->h};
	while (++i < g_n_players)
	{
		SDL_SetRenderDrawBlendMode(g_graph->screen.Renderer, SDL_BLENDMODE_BLEND);
		if (i == g_winner)
			SDL_RenderCopy(g_graph->screen.Renderer, g_graph->end[1], NULL, &pos);
		else
			SDL_RenderCopy(g_graph->screen.Renderer, g_graph->end[0], NULL, &pos);
		SDL_SetRenderDrawBlendMode(g_graph->screen.Renderer, SDL_BLENDMODE_NONE);
		pos.y += pos.h;
	}
	return (1);
}

void			ft_set_back_to_front(const unsigned int flags)
{
	SDL_Renderer	*renderer;
	static int		end = 0;

	if (end)
		return ;
	renderer = g_graph->screen.Renderer;
	ft_pcs_to_rack(g_frame->nb_pc, g_frame->pcs, flags, 0);
	SDL_RenderCopy(renderer, g_graph->marc_board, NULL,
		&(SDL_Rect){g_graph->big_square->x - 3, g_graph->big_square->y - 3,
		(g_graph->square->w - 1) * g_graph->cuant_squares[0] + 6,
		(g_graph->square->h - 1) * g_graph->cuant_squares[1] + 6});
	SDL_RenderCopy(renderer, g_graph->info_text, NULL,
		&(SDL_Rect){g_graph->screen.w * RIGHT_BORDER + g_graph->big_square->w
		+ 20, g_graph->screen.h * UPPER_BORDER, g_graph->square_info->w,
		g_graph->big_square->h});
	if (g_frame->prog_end)
		end = put_end_frame();
		SDL_RenderPresent(renderer);
	if (SDL_SetRenderDrawColor(g_graph->screen.Renderer, 0, 0, 0, 255))
		ft_sdl_error("SDL_SetRenderDrawColor", MODE_SDL);
	if (!g_frame->prog_end)
		SDL_RenderClear(renderer);
}
