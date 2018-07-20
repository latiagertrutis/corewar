/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 23:23:06 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/19 16:00:50 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void store_in_ram(t_player *player, t_board *board, unsigned char reg_pos, t_pc *pc)
{
	unsigned int	i;
	unsigned char	board_pos[IND_SIZE];
	unsigned short	pos;

	i = 0;
	pos = pc->pc + 3;
	while (i < IND_SIZE)
	{
		board_pos[IND_SIZE - 1 - i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{
		board[ft_mod((i + pc->pc + (*((short *)board_pos) % IDX_MOD)), MEM_SIZE)].mem =
			pc->reg[reg_pos][i];
		board[ft_mod((i + pc->pc + (*((short *)board_pos) % IDX_MOD)), MEM_SIZE)].id =
			player->id + 1;
		i++;
	}
	pc->pc = (pc->pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg1 + ind
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

static void	store_in_reg(unsigned char reg_pos1, unsigned char reg_pos2, t_pc *pc)
{
	unsigned int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		pc->reg[reg_pos2][i] = pc->reg[reg_pos1][i];
		i++;
	}
	pc->pc = (pc->pc + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2
	pc->carry = (!*((int *)(pc->reg[reg_pos1]))) ? 0x1 : 0x0;//actualizar carry
}

void		core_st(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos1;
	unsigned char	reg_pos2;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	if (ocp == 0x70 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_ram(player, arena->board, reg_pos1, pc);
	else if (ocp == 0x50 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER && (reg_pos2 = (arena->board[(pos + 3) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_reg(reg_pos1, reg_pos2, pc);
	else
		pc->pc = (pc->pc + 1) % MEM_SIZE;
}
