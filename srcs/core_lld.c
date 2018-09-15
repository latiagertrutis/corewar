/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:53:33 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/15 22:46:06 by mrodrigu         ###   ########.fr       */
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

static void		load_direct(t_board *board, const unsigned char reg_pos, t_pc *pc)
{
	unsigned char	i;
	unsigned short	aux_pc;

	i = 0;
	aux_pc = pc->pc;
	while (i < REG_SIZE)
	{//map into register
		pc->reg[reg_pos][i] = board[(aux_pc + 2 + i) % MEM_SIZE].mem;
		i++;
	}
//	ft_printf("\n****** ld (DIR)*******\nreg_pos: %u\ncont: ", reg_pos);
//	print_memory(pc->reg[reg_pos], 4, 4, 1);
//	ft_printf("*******************\n");
	pc->pc = (aux_pc + 1 + 1 + 1 + DIR_SIZE) % MEM_SIZE;//ld + opc + reg + dir
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

static void		load_indirect(t_board *board, const unsigned char reg_pos, t_pc *pc)
{
	unsigned char	board_pos[IND_SIZE];//the indirect
	unsigned char	i;
	unsigned short	aux_pc;

	i = 0;
	aux_pc = pc->pc;
	while (i < IND_SIZE)
	{//changing to big endian
		board_pos[IND_SIZE - 1 - i] = board[(aux_pc + 2 + i) % MEM_SIZE].mem;
		i++;
	}
	i = 0;
	while (i < REG_SIZE)
	{//acceding to indirect, and passing to register
		pc->reg[reg_pos][i] = board[ft_mod((i + aux_pc + (*((IND_CAST *)board_pos))), MEM_SIZE)].mem;
		i++;
	}
//	ft_printf("\n****** ld (IND)*******\nInd: %u\nreg_pos: %u\ncont: ", *((short *)board_pos), reg_pos);
//	print_memory(pc->reg[reg_pos], 4, 4, 1);
//	ft_printf("*******************\n");
	pc->pc = (aux_pc + 1 + 1 + 1 + IND_SIZE) % MEM_SIZE;//ld + opc + reg + ind
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

void			core_lld(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned short 	pos;
	unsigned char	ocp;
	unsigned char	reg_pos;

	pos = pc->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//pc + 1 = ocp, pc + 2 = first arg
	if (ocp == 0x90 && (reg_pos = arena->board[((pos + 2) + REG_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_direct(arena->board, reg_pos, pc);
	else if (ocp == 0xD0 && (reg_pos = arena->board[((pos + 2) + IND_SIZE) % MEM_SIZE].mem - 1) < REG_NUMBER)
		load_indirect(arena->board, reg_pos, pc);
	else//if ocp valid but not valid for this instruction jump what it sais
		pc->pc = (pc->pc + 1 + 1 + get_size_arg(ocp, 0, 1) + get_size_arg(ocp, 1, 1)) % MEM_SIZE;//ld + ocp + a1 + a2
}
