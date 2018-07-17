/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 02:59:04 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 17:52:07 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* static void	fill_board(t_arena *arena, int pc_pos, char *reg, const int size) */
/* { */
/* 	int i; */

/* 	i = 0; */
/* 	while(i < size) */
/* 	{ */
/* 		arena->board[pc_pos + i].mem = reg[size - 1 - i]; */
/* 		i++; */
/* 	} */
/* } */

/* static 	int charge_short(int size, t_arena *arena, int pc_pos) */
/* { */
/* 	int 	i; */
/* 	char	param[size]; */

/* 	i = 0; */
/* 	while(i < size) */
/* 	{ */
/* 		param[size - 1 - i] = arena->board[pc_pos + i].mem; */
/* 		i++; */
/* 	} */
/* 	return (*((unsigned short *)param)); */
/* } */

/* static 	int charge_int(int size, t_arena *arena, const int pc_pos, const int reg_nb) */
/* { */
/* 	int 	i; */
/* 	char	param[size]; */

/* 	i = 0; */
/* 	while(i < size) */
/* 	{ */
/* 		param[size - 1 - i] = arena->board[pc_pos + i].mem; */
/* 		i++; */
/* 	} */
/* 	return (*((unsigned int *)param)); */
/* } */

/* void 		core_sti(t_player *player, t_op op, t_arena *arena) */
/* { */
/* 	// S(RG), S(RG/ID/D2), S(ID/D2) */
/* 	//  1	1/2/2,	2/2 */
/* 	int  			param_size[3]; */
/* 	char 			ocp; */
/* 	unsigned int 	sum; */
/* 	int 			i; */
/* 	char 			reg_nb; */

/* 	sum = 0; */
/* 	i = 1; */
/* 	ocp = arena->board[player->pc + i].mem; */
/* 	param_size[0] = 1; //READ_REG SIZE */
/* 	i++; //PC + OP + OCP */
/* 	reg_nb = arena->board[i + player->pc].mem - 1; */
/* 	i += param_size[0]; // + p1(REG) */
/* 	param_size[2] = 2; */
/* 	if ((ocp & 0b00110000) >> 4 == REG_CODE) */
/* 	{ */
/* 		// exit(1); */
/* 		param_size[1] = 1; */
/* 	} */
/* 	else */
/* 		param_size[1] = 2; //READ_INDEX SIZE */
/* 	if (param_size[1] == 1) */
/* 	{ */
/* 		sum += charge_int(4, arena, i, reg_nb); */
/* 	} */
/* 	else */
/* 		sum += charge_short(param_size[1], arena, i); */
/* 	i += param_size[1]; */
/* 	sum += charge_short(param_size[2], arena, i); */
/* 	i += param_size[2] + sum; */
/* 	fill_board(arena, player->pc + sum, player->reg[reg_nb], REG_SIZE); */
/* 	player->pc += 1 + param_size[0] + param_size[1] + param_size[2]; //mana + 1 */
/* } */

void	core_sti(t_player *player, t_pc *pc, t_arena *arena)
{
	unsigned char	ocp;
	t_arg			arg2;
	t_arg			arg3;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	reg_pos = arena->board[(pc->pc + (2 % IDX_MOD)) % MEM_SIZE].mem - 1;
	arg2 = get_arg(ocp, pc->pc, arena->board, 1);
	arg3 = get_arg(ocp, pc->pc, arena->board, 2);
	if (!arg2.len || !arg3.len || arg3.type == IND_CODE)
	{
		pc->pc = (pc->pc + 1) % MEM_SIZE;
		return ;
	}
	get_arg_value(arena->board, &arg2, pc);
	get_arg_value(arena->board, &arg3, pc);
	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
	print_memory(arg2.arg, 4, 4, 1);
	ft_printf("arg3.len: %u\narg3.type: %u\n", arg3.len, arg3.type);
	print_memory(arg3.arg, 4, 4, 1);
	while (i < REG_SIZE)
	{
		arena->board[(pc->pc + ((*((uint32_t *)(arg2.arg)) + *((uint32_t *)(arg3.arg)) + i) % IDX_MOD)) % MEM_SIZE].mem = pc->reg[reg_pos][i];
		arena->board[(pc->pc + ((*((uint32_t *)(arg2.arg)) + *((uint32_t *)(arg3.arg)) + i) % IDX_MOD)) % MEM_SIZE].id = player->id + 1;
		i++;
	}
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
	pc->pc = (pc->pc + 1 + 1 + arg2.len + arg3.len + 1);//and + ocp + arg2 + arg3 + rg
}
