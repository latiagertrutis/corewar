/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/29 18:21:58 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_pcs_to_rack(t_sdl *Graph, t_data *data, int stela)
{
	unsigned int j;
	SDL_Rect	pc_rect;
	
	pc_rect = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	j = -1;
	while (++j < data->nb_pc)
	{
//		if (data->pc[j].pc > 4096)
//			ft_printf("El pc sa pasao primo");
		if (!data->pc[j].active)
			continue ;
		pc_rect.x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1)
			* ((data->pc[j].pc % MEM_SIZE) % Graph->cuant_squares[0]) + 1;
		pc_rect.y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1)
			* ((data->pc[j].pc % MEM_SIZE) / Graph->cuant_squares[1]);
		SDL_RenderCopy(Graph->screen.Renderer, Graph->pc[(int)data->pc[j].id + MAX_PLAYERS *
			stela], NULL, &pc_rect);
	}
}
