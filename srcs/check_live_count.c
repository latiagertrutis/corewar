/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:32:40 by mzabalza          #+#    #+#             */
/*   Updated: 2018/08/13 13:58:29 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


//recorrer todo los pc y eliminar los que no han dicho live

static void	reset_player(t_player *players, unsigned int nb_players)
{
	while (nb_players)
	{	
		ft_putstr("live counter ");
		ft_putstr(players[nb_players - 1].name);
		ft_putstr(": ");
		ft_putnbr(players[nb_players - 1].live_counter);
		ft_putchar(' ');
		ft_putnbr(players[nb_players - 1].last_live);
		ft_putchar('\n');
		players[--nb_players].live_counter = 0;
	}
		exit(1);

}

void 	check_live_count(t_data *data)
{
	unsigned int nbr_live;
	unsigned int k;

	nbr_live = 0;
	k = 0;
	while(k < data->nb_pc)
	{
		if (!(data->pc[k].live))
		{
			data->pc[k].active = 0x0;
			data->nb_pc_active--;
		}
		else
		{
			nbr_live += data->pc[k].live;
			data->pc[k].live = 0;
		}
		k++;
	}
	if (nbr_live >= NBR_LIVE || data->max_checks == MAX_CHECKS)
	{
		data->max_checks = 0;
		data->cycle_to_die -= CYCLE_DELTA;
	}
	else
		data->max_checks++;
	reset_player(data->players, data->n_players);
}
