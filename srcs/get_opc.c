/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 03:52:23 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/13 03:55:32 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_opc(t_board *board)
{
	char	opc[4];

	opc[0] = board[0].mem;
	opc[1] = board[1].mem;
	opc[2] = board[2].mem;
	opc[3] = board[3].mem;
	return(*((int *)opc));
}
