/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcs_to_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 07:37:31 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/25 19:50:57 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_pcs_to_rack(unsigned int n_players, t_sdl *Graph,
		t_player *players, int stela)
{
	unsigned int i;
	unsigned int j;
	SDL_Rect	pc_rect;
	
	i = 0;
	pc_rect = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	while (i < n_players)
	{
		j = 0;
		while (j < players[i].nb_pc)
		{
			pc_rect.x = Graph->screen.w * RIGHT_BORDER + (Graph->square->w - 1)
				* (players[i].pc[j].pc % Graph->cuant_squares[0]) + 1;
			pc_rect.y = Graph->screen.h * UPPER_BORDER + (Graph->square->h - 1)
				* (players[i].pc[j].pc / Graph->cuant_squares[1]) + 1;
			SDL_RenderCopy(Graph->screen.Renderer, Graph->pc[i + MAX_PLAYERS *
				stela], NULL, &pc_rect);
			j++;
			
		}
		i++;
	}
}
