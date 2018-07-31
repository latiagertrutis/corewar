/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 02:59:04 by mzabalza          #+#    #+#             */
/*   Updated: 2018/08/01 00:09:37 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			verify_ocp(const unsigned char ocp)
{
	if ((0xC & ocp) == 0xC || (0xC0 & ocp) == 0x80 || (0xC0 & ocp) == 0xC0 || (0xC0 & ocp) == 0x0 || (0x30 & ocp) == 0x0 || (0xC & ocp) == 0x0)
		return (0);
	return (1);

}

void			core_sti(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char	ocp;
	t_arg			arg2;
	t_arg			arg3;
	unsigned char	reg_pos;
	unsigned char	i;

	i = 0;
	ocp = arena->board[(pc->pc + 1) % MEM_SIZE].mem;//en pc + 1 esta ocp y en pc + 2 esta el primer argum
	if (verify_ocp (ocp))
	{
		reg_pos = arena->board[(pc->pc + 2) % MEM_SIZE].mem - 1;
		arg2 = (t_arg){1, 0, 0, 0x0, {0}};
		arg3 = (t_arg){2, 0, 0, 0x0, {0}};
		get_arg(ocp, pc->pc, arena->board, &arg2);
		get_arg(ocp, pc->pc, arena->board, &arg3);
		if 	(get_arg_value(arena->board, &arg2, pc) && get_arg_value(arena->board, &arg3, pc))
		{
			invert_bytes(arg2.arg, arg2.type == DIR_CODE ? 2 : 4);
			invert_bytes(arg3.arg, arg3.type == DIR_CODE ? 2 : 4);
			if (arg2.type == DIR_CODE)
				*((int *)arg2.arg) = *((short *)arg2.arg);
			if (arg3.type == DIR_CODE)
				*((int *)arg3.arg) = *((short *)arg3.arg);
			while (i < REG_SIZE)
			{//con idx mod es el resto puesto que es un rango y puede optar a valores negativos en cambio MEM_SIZE precisa de ser un modulo puesto que la memoria es circular y en ningun caso puede ser negativo
				arena->board[ft_mod((pc->pc + i + ((*((int *)(arg2.arg)) + *((int *)(arg3.arg))) % IDX_MOD)), MEM_SIZE)] =
					(t_board){pc->reg[reg_pos][i], pc->id, 0x1};
				i++;
			}
		}
		pc->pc = (pc->pc + 1 + 1 + arg2.len + arg3.len + get_size_arg(ocp, 0, 0)) % MEM_SIZE;//and + ocp + arg2 + arg3 + rg
	}
	else
		pc->pc = (pc->pc + 1 + 1 + get_size_arg(ocp, 0, 0) + get_size_arg(ocp, 1, 0) + get_size_arg(ocp, 2, 0)) % MEM_SIZE;//and + ocp + arg1 + arg2 + rg
}
// ft_printf("************ STI *****************\narg2 tipo %d cont: \n", arg2.type);
// print_memory(arg2.arg, 4, 4, 1);
// ft_printf("arg3 tipo: %u cont:\n", arg3.type);
// print_memory(arg3.arg, 4, 4, 1);
// ft_printf("reg: \n");
// print_memory(pc->reg[reg_pos], 4, 4, 1);
// ft_printf("el pc es %d\n", (pc - player->pc));
// ft_printf("**********************************\n");

//	ft_printf("la direccion es: %d\n", -38 % IDX_MOD)//ft_mod((pc->pc + ft_mod((*((int *)(arg2.arg)) + *((int *)(arg3.arg)) + i), IDX_MOD)), MEM_SIZE));
//	exit(1);
