/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 07:09:33 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/22 13:52:45 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/* static unsigned int		get_num(t_board *board, const unsigned char ocp, const unsigned char n_arg, const t_player *player) */
/* { */
/* 	unsigned char type; */
/* 	unsigned char *aux; */
/* 	unsigned int	num; */

/* 	aux = NULL; */
/* 	type = (ocp & (0xC0 >> (2 * n_arg))) >> (2 * (3 - n_arg)); */
/* 	if (type == REG_CODE) */
/* 	{ */
/* 		num = *((unsigned int *)(player->reg[board[player->pc + 2 + 2].mem - 1]));//mirar esto aqui hay que hacer generico ese + 2 */
/* 		print_memory(&num, 4, 16, 1); */
/* 		exit (1); */
/* 		invert_bytes(&num, sizeof(unsigned int)); */
/* 		return (num); */
/* 	} */
/* 	if (type == DIR_CODE) */
/* 	{ */
/* 		aux = get_mem_board(board + player->pc + 2 + n_arg, DIR_SIZE); */
/* 		num = *((unsigned int *)aux); */
/* 		invert_bytes(&num, sizeof(unsigned int)); */
/* 		free(aux); */
/* 		return(num); */
/* 	} */
/* 	aux = get_mem_board(board + player->pc + 2 + n_arg, IND_SIZE); */
/* 	num = *((unsigned short *)aux); */
/* 	invert_bytes(&num, sizeof(unsigned short)); */
/* 	free(aux); */
/* 	aux = get_mem_board(board + player->pc + num, DIR_SIZE); */
/* 	num = *((unsigned int *)aux); */
/* 	invert_bytes(&num, sizeof(unsigned int)); */
/* 	free(aux); */
/* 	return (num); */
/* } */

/* static void		operate(t_player *player, const unsigned char ocp, t_board *board) */
/* { */
/* 	unsigned int	num1; */
/* 	unsigned int	num2; */
/* 	unsigned int	res; */
/* 	unsigned char	reg_pos; */

/* 	reg_pos = board[player->pc + 2 + get_size(ocp, 0) + get_size(ocp, 1)].mem - 1; */
/* 	num1 = get_num(board, ocp, 0, player); */
/* 	num2 = get_num(board, ocp, 1, player); */
/* 	res = num1 & num2; */
/* 	invert_bytes(&res, sizeof(unsigned int)); */
/* 	ft_memcpy(player->reg[reg_pos], &res, REG_SIZE); */
/* 	player->pc = (player->pc + 1 + 1 + get_size(ocp, 0) + get_size(ocp, 1) + 1) % MEM_SIZE;//ld + opc + arg1 + arg2 + reg */
/* 	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry */
/* } */



/* static void			operate(t_player *player, t_arg *arg1, t_arg *arg2, t_board *board) */
/* { */
/* 	unsigned char	reg_pos; */
/* 	unsigned char	i; */

/* 	i = 0; */
/* 	reg_pos = board[(player->pc + ((2 + arg1->len + arg2->len) % IDX_MOD)) % MEM_SIZE].mem - 1; */
/* 	get_value(player, board, arg1); */
/* 	get_value(player, board, arg2); */
/* 	ft_printf("arg1.len: %u\narg1.type: %u\n", arg1->len, arg1->type); */
/* 	print_memory(arg1->arg, 4, 4, 1); */
/* 	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2->len, arg2->type); */
/* 	print_memory(arg2->arg, 4, 4, 1); */
/* 	while (i < REG_SIZE) */
/* 	{ */
/* 		player->reg[reg_pos][i] = arg1->arg[i] & arg2->arg[i]; */
/* 		i++; */
/* 	} */
/* 	ft_printf("res en %u es: \n", reg_pos); */
/* 	print_memory(player->reg[reg_pos], 4, 4, 1); */
/* 	player->carry = (!*((int *)(player->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry */
/* } */



void				core_and(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg1;
	t_arg			arg2;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	arg1 = (t_arg){0, 0, 0, 0x1, {0}};
	arg2 = (t_arg){1, 0, 0, 0x1, {0}};
	get_arg(ocp, pc->pc, arena->board, &arg1);
	get_arg(ocp, pc->pc, arena->board, &arg2);
	if (!arg1.len || !arg2.len)
	{
		pc->pc = (pc->pc + 1) % MEM_SIZE;
		return ;
	}
	reg_pos = arena->board[(pc->pc + ((2 + arg1.len + arg2.len) % IDX_MOD)) % MEM_SIZE].mem - 1;
//	get_arg_value(arena->board, &arg1, pc);
//	get_arg_value(arena->board, &arg2, pc);
//	ft_printf("arg1.len: %u\narg1.type: %u\n", arg1.len, arg1.type);
//	print_memory(arg1.arg, 4, 4, 1);
//	ft_printf("arg2.len: %u\narg2.type: %u\n", arg2.len, arg2.type);
//	print_memory(arg2.arg, 4, 4, 1);
	*((uint32_t *)(pc->reg[reg_pos])) = *((uint32_t *)(arg1.arg)) & *((uint32_t *)(arg2.arg));
//	ft_printf("res en %u es: \n", reg_pos);
//	print_memory(pc->reg[reg_pos], 4, 4, 1);
	pc->carry = (!*((int *)(pc->reg[reg_pos]))) ? 0x1 : 0x0;//actualizar carry
	pc->pc = (pc->pc + 1 + 1 + arg1.len + arg2.len + 1) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
