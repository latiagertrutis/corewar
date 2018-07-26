/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_champs_to_arena.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 23:56:45 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/12 02:50:42 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		fill_region(t_pc pc, const t_data *data, const unsigned int i, const unsigned int inc)
{
	unsigned int j;

	j = 0;
	pc.pc = j + i * inc;
	while (j < data->players[i].prog_size)
	{
		data->arena->board[j + i * inc] = (t_board){data->players[i].prog[j], data->players[i].id + 1};
		j++;
	}
}

void			put_champs_to_arena(const t_data *data)
{
	unsigned int	inc;
	unsigned int	i;

	inc = MEM_SIZE / data->n_players;
	i = 0;
	while (i < data->n_players)
	{
		fill_region(data->pc[i], data, i, inc);
		i++;
	}
}
