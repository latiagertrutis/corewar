/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_back_to_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:19:40 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/24 22:39:50 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void			ft_set_back_to_front(const unsigned int flags)
{
	SDL_Renderer *Renderer;

	Renderer = g_Graph->screen.Renderer;
	SDL_RenderCopy(Renderer, g_Graph->screen.texture, NULL, g_Graph->big_square);
	ft_pcs_to_rack(g_frame->nb_pc, g_frame->pcs, flags, 0);
	SDL_RenderCopy(g_Graph->screen.Renderer, g_Graph->info_text, NULL, &(SDL_Rect){g_Graph->screen.w * RIGHT_BORDER + g_Graph->big_square->w + 20, g_Graph->screen.h * UPPER_BORDER, g_Graph->square_info->w, g_Graph->big_square->h});
	SDL_RenderPresent(Renderer);
	ft_pcs_to_rack(g_frame->nb_pc, g_frame->pcs, flags, 1);
	if (SDL_SetRenderDrawColor(g_Graph->screen.Renderer, 0, 0, 0, 0))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
//	SDL_RenderClear(Renderer);
}
