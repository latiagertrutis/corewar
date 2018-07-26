/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 02:57:42 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/25 02:57:44 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	check_winner(t_player *players, int nb_players)
{
	int 		i;
	t_player 	*winner;

	i = 0;
	winner = &players[i++];
	while (i < nb_players)
	{
		if (players[i].last_live > winner->last_live)
			winner = &players[i];
		i++;
	}
	ft_printf("Contestant %d, %s, has won!\n", (int)winner->id, winner->name);
}