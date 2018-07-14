/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 07:09:33 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/14 10:08:38 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned char	get_size(const unsigned char ocp, const unsigned char n_arg)
{
	unsigned char type;

	type = (ocp & (0xC0 >> (2 * n_arg))) >> (2 * (3 - n_arg));
	if (type == REG_CODE)
		return (1);
	if (type == DIR_CODE)
		return (4);
	return (2);
}

static unsigned int		get_num(t_board *board, const unsigned char ocp, const unsigned char n_arg, const t_player *player)
{
	unsigned char type;
	unsigned char *aux;
	unsigned int	num;

	aux = NULL;
	type = (ocp & (0xC0 >> (2 * n_arg))) >> (2 * (3 - n_arg));
	if (type == REG_CODE)
	{
		num = *((unsigned int *)(player->reg[board[player->pc + 2 + 2].mem - 1]));//mirar esto aqui hay que hacer generico ese + 2
		print_memory(&num, 4, 16, 1);
		exit (1);
		invert_bytes(&num, sizeof(unsigned int));
		return (num);
	}
	if (type == DIR_CODE)
	{
		aux = get_mem_board(board + player->pc + 2 + n_arg, DIR_SIZE);
		num = *((unsigned int *)aux);
		invert_bytes(&num, sizeof(unsigned int));
		free(aux);
		return(num);
	}
	aux = get_mem_board(board + player->pc + 2 + n_arg, IND_SIZE);
	num = *((unsigned short *)aux);
	invert_bytes(&num, sizeof(unsigned short));
	free(aux);
	aux = get_mem_board(board + player->pc + num, DIR_SIZE);
	num = *((unsigned int *)aux);
	invert_bytes(&num, sizeof(unsigned int));
	free(aux);
	return (num);
}

static void		operate(t_player *player, const unsigned char ocp, t_board *board)
{
	unsigned int	num1;
	unsigned int	num2;
	unsigned int	res;
	unsigned char	reg_pos;

	reg_pos = board[player->pc + 2 + get_size(ocp, 0) + get_size(ocp, 1)].mem - 1;
	num1 = get_num(board, ocp, 0, player);
	num2 = get_num(board, ocp, 1, player);
	res = num1 & num2;
	invert_bytes(&res, sizeof(unsigned int));
	ft_memcpy(player->reg[reg_pos], &res, REG_SIZE);
	player->pc = (player->pc + 1 + 1 + get_size(ocp, 0) + get_size(ocp, 1) + 1) % MEM_SIZE;//ld + opc + arg1 + arg2 + reg
	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
}

void				core_and(t_player *player, t_op op, t_arena *arena)
{
	unsigned short 	pos;
	unsigned char	ocp;

	pos = player->pc;
	ocp = arena->board[(pos + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	operate(player, ocp, arena->board);
}
