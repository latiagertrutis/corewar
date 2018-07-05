/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:34:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/01 00:34:37 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int init_players(t_player **players, int ac)
{
	if (!(*players = (t_player *)malloc(sizeof(t_player) * ac)))
		return (0);
	(*players)->content = NULL;
	(*players)->name = NULL;
	(*players)->prog = NULL;
	return (1);

}

static int init_arena(t_arena **arena)
{
	if (!(*arena = (t_arena *)malloc(sizeof(t_arena))))
		return (0);
	ft_memset((*arena)->board, 0, MEM_SIZE);
	return (1);

}

int 	init_corewar(t_arena **arena, t_player **players, int ac)
{
	if (!init_arena(arena))
		return (0);
	if (!init_players(players, ac))
		return (0);
	return (1);
}