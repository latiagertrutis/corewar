/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 23:23:06 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/14 04:23:41 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void store_in_ram(t_player *player, t_board *board, unsigned char reg_pos, unsigned short pos)
{
	unsigned int	i;
	unsigned char	board_pos[IND_SIZE];

	i = 0;
	while (i < IND_SIZE)
	{
		board_pos[IND_SIZE - 1 - i] = board[(pos + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{
		board[(i + player->pc + (*((unsigned short *)board_pos) % IDX_MOD)) % MEM_SIZE].mem =
			player->reg[reg_pos][i];
		board[(i + player->pc + (*((unsigned short *)board_pos) % IDX_MOD)) % MEM_SIZE].id =
			player->id + 1;
		i++;
	}
	player->pc = (player->pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg1 + ind
	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

static void	store_in_reg(t_player *player, unsigned char reg_pos1, unsigned char reg_pos2)
{
	unsigned int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		player->reg[reg_pos2][i] = player->reg[reg_pos1][i];
		i++;
	}
	player->pc = (player->pc + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2
	player->carry = (!*((int *)(player->reg[reg_pos1]))) ? 0x1 : 0x0;//actualizar carry
}

void		core_st(t_player *player, t_op op, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos1;
	unsigned char	reg_pos2;

	pos = player->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	if (ocp == 0x70 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_ram(player, arena->board, reg_pos1, pos + 3);
	else if (ocp == 0x50 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER && (reg_pos2 = (arena->board[(pos + 3) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_reg(player, reg_pos1, reg_pos2);
}
