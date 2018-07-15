/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 02:59:04 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/13 02:59:54 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	fill_board(t_arena *arena, int pc_pos, char *reg, const int size)
{
	int i;

	i = 0;
	while(i < size)
	{
		arena->board[pc_pos + i].mem = reg[size - 1 - i];
		i++;
	}
}

static 	int charge_short(int size, t_arena *arena, int pc_pos)
{
	int 	i;
	char	param[size];

	i = 0;
	while(i < size)
	{
		param[size - 1 - i] = arena->board[pc_pos + i].mem;
		i++;
	}
	return (*((unsigned short *)param));
}

static 	int charge_int(int size, t_arena *arena, const int pc_pos, const int reg_nb)
{
	int 	i;
	char	param[size];

	i = 0;
	while(i < size)
	{
		param[size - 1 - i] = arena->board[pc_pos + i].mem;
		i++;
	}
	return (*((unsigned int *)param));
}

void 		core_sti(t_player *player, t_op op, t_arena *arena)
{
	// S(RG), S(RG/ID/D2), S(ID/D2)
	//  1	1/2/2,	2/2
	int  			param_size[3];
	char 			ocp;
	unsigned int 	sum;
	int 			i;
	char 			reg_nb;

	sum = 0;
	i = 1;
	ocp = arena->board[player->pc + i].mem;
	param_size[0] = 1; //READ_REG SIZE
	i++; //PC + OP + OCP
	reg_nb = arena->board[i + player->pc].mem - 1;
	i += param_size[0]; // + p1(REG)
	param_size[2] = 2;
	if ((ocp & 0b00110000) >> 4 == REG_CODE)
	{
		// exit(1);
		param_size[1] = 1;
	}
	else
		param_size[1] = 2; //READ_INDEX SIZE
	if (param_size[1] == 1)
	{
		sum += charge_int(4, arena, i, reg_nb);
	}
	else
		sum += charge_short(param_size[1], arena, i);
	i += param_size[1];
	sum += charge_short(param_size[2], arena, i);
	i += param_size[2] + sum;
	fill_board(arena, player->pc + sum, player->reg[reg_nb], REG_SIZE);
	player->pc += 1 + param_size[0] + param_size[1] + param_size[2]; //mana + 1
}
