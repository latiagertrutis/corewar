/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 23:23:06 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/26 19:46:10 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void store_in_ram(t_board *board, unsigned char reg_pos, t_pc *pc)
{
	unsigned int	i;
	char			board_pos[IND_SIZE];
	unsigned short	aux_pc;

	i = 0;
	aux_pc = pc->pc;
	while (i < IND_SIZE)
	{
		board_pos[IND_SIZE - 1 - i] = board[(aux_pc + 3 + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{
		board[ft_mod((i + aux_pc + (*((short *)board_pos) % IDX_MOD)), MEM_SIZE)] = (t_board){pc->reg[reg_pos][i], pc->id, 0x1};
		i++;
	}
//	ft_printf("\n****** st (IND)*******\nInd: %u\nreg_pos: %u\ncont: ", *((short *)board_pos), reg_pos);
//	print_memory(pc->reg[reg_pos], 4, 4, 1);
//	ft_printf("*******************\n");
	pc->pc = (aux_pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg1 + ind
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
//	ft_printf("\n****** st (REG/REG) *******\reg_pos1: %u\nreg_pos2: %u\ncont: ", reg_pos1, reg_pos2);
//	print_memory(pc->reg[reg_pos1], 4, 4, 1);
//	print_memory(pc->reg[reg_pos2], 4, 4, 1);
//	ft_printf("*******************\n");
	pc->pc = (pc->pc + 1 + 1 + 1 + 1) % MEM_SIZE;//ld + opc + reg1 + reg2
}

void		core_st(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos1;
	unsigned char	reg_pos2;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argumento
	if (ocp == 0x70 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_ram(arena->board, reg_pos1, pc);
	else if (ocp == 0x50 && (reg_pos1 = (arena->board[(pos + 2) % MEM_SIZE].mem - 1)) < REG_NUMBER &&
	         (reg_pos2 = (arena->board[(pos + 3) % MEM_SIZE].mem - 1)) < REG_NUMBER)
		store_in_reg(reg_pos1, reg_pos2, pc);
	else if (!check_ocp(ocp))
		pc->pc = (pc->pc + 2) % MEM_SIZE;
	else
		pc->pc = (pc->pc + 1 + get_size_arg(ocp, 0, 1) + get_size_arg(ocp, 1, 1) + get_size_arg(ocp, 2, 1)) % MEM_SIZE;
}
