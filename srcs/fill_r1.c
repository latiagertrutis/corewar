/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_r1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 23:45:52 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/12 23:45:55 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// meto el numero de jugador en el registro 1
void			fill_r1(t_data *data)
{
	int i;

	i = 0;
	while(i < data->n_players)
	{
		ft_memcpy(data->players[i].reg[0], &(data->players[i].player_nb), 4);
		i++;
	}
}
