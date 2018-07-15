/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 03:43:25 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/15 10:05:30 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ocp =  11   11   11      00
**       1arg 2arg 3arg   no susa
*/

/*
** POSSIBLE CAST TO GENERIC
*/

static void		load_direct(t_player *player, t_board *board, const unsigned char reg_pos, const unsigned short pos)
{
	unsigned char	i;

	i = 0;
	while (i < REG_SIZE)
	{//copia de lo que hay en el mapa en el registro
		player->reg[reg_pos][i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	player->pc = (player->pc + 1 + 1 + 1 + DIR_SIZE) % MEM_SIZE;//ld + opc + reg + dir
	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

static void		load_indirect(t_player *player, t_board *board, const unsigned char reg_pos, const unsigned short pos)
{
	unsigned char	board_pos[IND_SIZE];//el indirecto (2)
	unsigned char	i;

	i = 0;
	while (i < IND_SIZE)
	{//copia de lo que hay en el mapa en board_pos
		board_pos[IND_SIZE - 1 - i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{//accediendo mediante el anterior indirecto se copia en el registro lo apuntado
		player->reg[reg_pos][i] = board[(i + player->pc + (*(( short *)board_pos) % IDX_MOD)) % MEM_SIZE].mem;
		i++;
	}
	player->pc = (player->pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg + ind
	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

void			core_ld(t_player *player, t_op op, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos;

	pos = player->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	//si p1 es un directo
	if (ocp == 0x90 && (reg_pos = arena->board[((pos + 2) + REG_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_direct(player, arena->board, reg_pos, pos + 2);
	else if (ocp == 0xD0 && (reg_pos = arena->board[((pos + 2) + IND_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_indirect(player, arena->board, reg_pos, pos + 2);
//	load_data(player, arena->board, ++pos, ocp);
	print_memory(player->reg[(*(arena->board + (pos + 2) + IND_SIZE)).mem - 1], 4, 16, 1);
//	print_memory(player->reg[(*(arena->board + (pos + 2) + REG_SIZE)).mem - 1], 4, 16, 1);
//	exit(1);
}
