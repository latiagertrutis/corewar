/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 02:59:04 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/13 02:59:54 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static 	nb_from_size(int size, t_player *player, t_arena *arena, int j)
{
	int 	i;
	char	param[size];

	i = 0;
	while(i < size)
	{
		param[i] = arena->board[player->pc + j + i].mem;
		i++;
	}
	return (*((int *)param));
}

void 	core_sti((t_player *player, t_op op, t_arena *arena)
{
	// S(RG), S(RG/ID/D2), S(ID/D2)
	//  1	1/2/2, 		2/2
	int  	param_size[3];
	char 	ocp;
	int 	sum;
	int 	i;

	sum = 0;
	ocp = arena->board[player->pc].mem;
	param_size[0] = 1;
	i = 2; //
	param_size[2] = 2;
	if ((opc & 0x00FF0000) == 0x01)
		param_size[1] = 1;
	else
		param_size[1] = 2;
	sum += nb_from_size(param_size[1], player, arena, i);
	i += param_size[1];
	sum += nb_from_size(param_size[2], player, arena, i);
	i += param_size[2];
	arena->board[player->pc + i].mem


}
