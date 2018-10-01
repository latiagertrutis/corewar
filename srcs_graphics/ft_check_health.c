/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_health.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 23:02:41 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/01 19:50:28 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		place_heart(int dist, int cicle_pre_die, int top[4], int player)
{
	SDL_Rect	heart;
	int			i;
	int			pos;

	i = 0;
	while (cicle_pre_die <= top[player] && i < 4)
	{
		pos = cicle_pre_die * 7 * 4 / top[player];
		if ((pos + 1) > i * 7 && (pos + 1) <= (i + 1) * 7)
		{
			pos -= i * 7;
			heart = (SDL_Rect){g_graph->heart_pos->x + dist * i,
				g_graph->heart_pos->y + (g_graph->info_marc->h) *
				player, g_graph->heart[pos]->w, g_graph->heart[pos]->h};
			ft_surf_to_text(g_graph->info_text, g_graph->heart[pos], &heart);
		}
		i++;
	}
}

void			ft_check_health(const int cycle_to_die, int player,
			int cicle_pre_die, const t_player *players)
{
	static int	top[4] = {0, 0, 0, 0};
	int			dist;

	if (!top[player])
		top[player] = cycle_to_die;
	dist = (g_graph->player_nbr->w * 20 - g_graph->heart_pos->w * 4) /
		3 + g_graph->heart_pos->w;
	if (players[player].live_counter)
	{
		top[player] = cycle_to_die;
		ft_reset_health(player, g_graph->heart_pos, g_graph->info_marc,
			g_graph->heart[0]);
		return ;
	}
	place_heart(dist, cicle_pre_die, top, player);
}
