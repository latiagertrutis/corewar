/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_back_to_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:19:40 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/25 01:38:36 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_set_back_to_front(t_sdl *Graph)
{
	SDL_Renderer *Renderer;

	Renderer = Graph->screen.Renderer;
	SDL_RenderCopy(Renderer, Graph->screen.texture, NULL, Graph->big_square);
	SDL_RenderCopy(Graph->screen.Renderer, Graph->info_text, NULL, &(SDL_Rect){Graph->screen.w * RIGHT_BORDER + Graph->big_square->w, Graph->screen.h * UPPER_BORDER, Graph->square_info->w, Graph->big_square->h});
	SDL_RenderPresent(Renderer);
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, BACK_COLOR
			SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	SDL_RenderClear(Renderer);
}
