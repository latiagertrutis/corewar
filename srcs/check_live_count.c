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

void 	check_live_count(t_player *players, int nb_players)
{
	int i;

	i = 0;
	while(i < nb_players)
	{
		if ((players[i].live_counter))
			players[i].live_counter = 0;
		else
		{
			ft_printf("Jugador %s is dead", players[i].name); //decidir que hacer cuando muere
			exit(1);
		}
		i++;
	}
}