/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 03:43:25 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/13 07:12:30 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ocp =  11   11   11      00
**       1arg 2arg 3arg   no susa
*/

static void		load_data(t_player *player, t_board *board, int ocp)
{
	unsigned char	reg_pos;
	unsigned char	*board_pos;
	unsigned char	*buff;

	if (ocp == 0x90 && (reg_pos = (*(board + REG_SIZE)).mem) < REG_NUMBER)
	{
		buff = get_mem_board(board, REG_SIZE);
		ft_memcpy(player->reg[reg_pos], buff, REG_SIZE);
		free(buff);
		return ;
	}
	if (ocp == 0xD0 && (reg_pos = (*(board + IND_SIZE)).mem) < REG_NUMBER)
	{
		board_pos = get_mem_board(board, IND_SIZE);
		buff = get_mem_board(board + (*((unsigned short *)board_pos) % IDX_MOD), REG_SIZE);
		ft_memcpy(player->reg[reg_pos], buff, REG_SIZE);
		free(board_pos);
		free(buff);
	}

}

void			core_ld(t_player *player, t_op op, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;

	pos = player->pc;
	ocp = arena->board[++pos].mem;
	load_data(player, arena->board + (++pos), ocp);
}
