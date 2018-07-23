/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:32:40 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/12 18:32:45 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	check_live_count(t_player *players, int nb_players, t_data *data)
{
	unsigned int nbr_live;
	int i;

	nbr_live = 0;
	i = 0;
	while(i < nb_players)
	{
		if ((players[i].live_counter))
		{
			nbr_live += players[i].live_counter;
			players[i].live_counter = 0;
		}
		else
		{
			ft_printf("Jugador %s is dead", players[i].name); //decidir que hacer cuando muere
			exit(1);
		}
		i++;
	}
	if (nbr_live >= NBR_LIVE || data->max_checks == MAX_CHECKS)
	{
		data->max_checks = 0;
		data->cycle_to_die -= CYCLE_DELTA;
	}
	else
		data->max_checks++;
}