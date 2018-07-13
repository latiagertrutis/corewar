/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 03:43:25 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/13 10:55:22 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ocp =  11   11   11      00
**       1arg 2arg 3arg   no susa
*/

static void		load_data(t_player *player, t_board *board, unsigned short pos, int ocp)
{
	unsigned char	reg_pos;
	unsigned char	*board_pos;
	unsigned char	*buff;

	buff = NULL;
	board_pos = NULL;
	if (ocp == 0x90 && (reg_pos = (*(board + pos + REG_SIZE)).mem - 1) < REG_NUMBER)
	{
		buff = get_mem_board(board + pos, REG_SIZE);//obtener el valor del directo
		ft_memcpy(player->reg[reg_pos], buff, REG_SIZE);
		player->pc += 1 + 1 + 1 + REG_SIZE;//ld + opc + reg + ind
	}
	else if (ocp == 0xD0 && (reg_pos = (*(board + pos + IND_SIZE)).mem - 1) < REG_NUMBER)
	{
		board_pos = get_mem_board(board + pos, IND_SIZE);//obtener el valor del indirecto
		invert_bytes(board_pos, IND_SIZE);
		buff = get_mem_board(board + ((*((unsigned short *)board_pos)
		+ player->pc) % IDX_MOD), REG_SIZE);//acceder a la posicion (pc + indirecto) % idx
		ft_memcpy(player->reg[reg_pos], buff, REG_SIZE);
		free(board_pos);
		player->pc += 1 + 1 + 1 + IND_SIZE;//ld + opc + reg + dir
	}
	player->carry = (buff && !*((int *)buff)) ? 0x1 : 0x0;
	free(buff);
}

void			core_ld(t_player *player, t_op op, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;

	pos = player->pc;
	ocp = arena->board[++pos].mem;
	load_data(player, arena->board, ++pos, ocp);
//	print_memory(player->reg[(*(arena->board + pos + IND_SIZE)).mem - 1], 4, 16, 1);
//	print_memory(player->reg[(*(arena->board + pos + REG_SIZE)).mem - 1], 4, 16, 1);
//	exit(1);
}
