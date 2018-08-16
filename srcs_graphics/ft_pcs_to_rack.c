/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/16 16:19:12 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_pcs_to_rack(t_sdl *Graph, t_data *data, int stela)
{
	unsigned int j;
	SDL_Rect	pc_rect;
	t_pc		*pc;

	pc = data->pc;
	pc_rect = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	j = -1;
	while (++j < data->nb_pc)
	{
		if (!pc[j].active)
			continue ;
		pc_rect.x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1)
			* ((pc[j].pc % MEM_SIZE) % Graph->cuant_squares[0]) + 2;
		pc_rect.y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1)
			* ((pc[j].pc % MEM_SIZE) / Graph->cuant_squares[1]) + 1;
		SDL_RenderCopy(Graph->screen.Renderer,
			Graph->pc[(int)pc[j].id + 8 - data->mods->info * 8 +
			MAX_PLAYERS * stela], NULL, &pc_rect);
	}
}
