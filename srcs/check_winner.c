/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 02:57:42 by mzabalza          #+#    #+#             */
/*   Updated: 2018/08/13 14:09:31 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	check_winner(t_player *players, int nb_players)
{
	int 		i;
	t_player 	*winner;

	i = nb_players;
	winner = &players[--i];
	while (i)
	{
		if (players[i - 1].last_live > winner->last_live)
			winner = &players[i - 1];
		i--;
	}
	ft_printf("Contestant %d, %s, has won!\n", (int)winner->id, winner->name);
}
