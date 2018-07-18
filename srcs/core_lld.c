/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:53:33 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/17 17:56:16 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		load_direct(t_board *board, const unsigned char reg_pos, t_pc *pc)
{
	unsigned char	i;
	unsigned short	pos;

	i = 0;
	pos = pc->pc + 2;
	while (i < REG_SIZE)
	{//copia de lo que hay en el mapa en el registro
		pc->reg[reg_pos][i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	pc->pc = (pc->pc + 1 + 1 + 1 + DIR_SIZE) % MEM_SIZE;//ld + opc + reg + dir
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

static void		load_indirect(t_board *board, const unsigned char reg_pos, t_pc *pc)
{
	unsigned char	board_pos[IND_SIZE];//el indirecto (2)
	unsigned char	i;
	unsigned short pos;

	i = 0;
	pos = pc->pc + 2;
	while (i < IND_SIZE)
	{//copia de lo que hay en el mapa en board_pos
		board_pos[IND_SIZE - 1 - i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{//accediendo mediante el anterior indirecto se copia en el registro lo apuntado
		pc->reg[reg_pos][i] = board[(i + pc->pc + *(( short *)board_pos)) % MEM_SIZE].mem;
		i++;
	}
	pc->pc = (pc->pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg + ind
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

void			core_lld(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	//si p1 es un directo
	if (ocp == 0x90 && (reg_pos = arena->board[((pos + 2) + REG_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_direct(arena->board, reg_pos, pc);
	else if (ocp == 0xD0 && (reg_pos = arena->board[((pos + 2) + IND_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_indirect(arena->board, reg_pos, pc);
	else
		pc->pc = (pc->pc + 1) % MEM_SIZE;
//	load_data(player, arena->board, ++pos, ocp);
	print_memory(pc->reg[(*(arena->board + (pos + 2) + IND_SIZE)).mem - 1], 4, 16, 1);
//	print_memory(pc->reg[(*(arena->board + (pos + 2) + REG_SIZE)).mem - 1], 4, 16, 1);
//	exit(1);
}