/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_r1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 23:45:52 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 14:32:06 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// meto el numero de jugador en el registro 1
void			fill_r1(t_data *data)
{
	unsigned int 	i;
	unsigned int 	j;
	t_player		*player;
	unsigned int	n_players;

	i = 0;
	player = data->players;
	n_players = data->n_players;
	while(i < n_players)
	{
		j = 0;
		while (j < player[i].nb_pc)
		{
			ft_memcpy(player[i].pc[j].reg[0], &(player[i].player_nb), sizeof(int));
			j++;
		}
		i++;
	}
}
