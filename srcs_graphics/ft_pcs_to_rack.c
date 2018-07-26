/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/26 19:25:00 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_pcs_to_rack(t_sdl *Graph, t_data *data, int stela)
{
	unsigned int j;
	SDL_Rect	pc_rect;
	
	pc_rect = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	j = 0;
	ft_printf("hay %i pcs\n", data->nb_pc);
	while (j < data->nb_pc)
	{
		ft_printf("data->pc[%i].id = %i y esta en %i\n", j, data->pc[j].id, data->pc[j].pc);
		pc_rect.x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1)
			* (data->pc[j].pc % Graph->cuant_squares[0]) + 1;
		pc_rect.y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1)
			* (data->pc[j].pc / Graph->cuant_squares[1]) + 1;
		SDL_RenderCopy(Graph->screen.Renderer, Graph->pc[(int)data->pc[j].id + MAX_PLAYERS *
			stela], NULL, &pc_rect);
		j++;		
	}
}
