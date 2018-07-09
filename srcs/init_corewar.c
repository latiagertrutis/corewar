/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:34:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/09 00:09:40 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int init_players(t_data *data)
{
	if (!(data->players = (t_player *)ft_memalloc(sizeof(t_player) * data->n_players)))
		return (0);
	return (1);

}

static int init_arena(t_data *data)
{
	if (!(data->arena = (t_arena *)ft_memalloc(sizeof(t_arena))))
		return (0);
	return (1);

}

int 	init_corewar(t_data *data)
{
	if (!init_arena(data))
		return (0);
	if (!init_players(data))
		return (0);
	return (1);
}
