/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:44:28 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 16:44:30 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int 	charge_short(int size, t_arena *arena, int pc_pos)
{
	int 	i;
	char	param[size];

	i = 0;
	while(i < size)
	{
		param[size - 1 - i] = arena->board[(pc_pos + i) % MEM_SIZE].mem;
		i++;
	}
	print_memory(param, size, size, 1);
	return (*((unsigned short *)param));
}

static 	int charge_int(int size, t_arena *arena, const int pc_pos)
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

void		core_aff(t_player *player, t_pc *pc, t_arena *arena)
{
	char 			reg_nb;
	char 			reg_content;

	reg_nb = arena->board[(pc->pc + 1) % MEM_SIZE].mem;
	reg_content = (charge_int(sizeof(int), arena, (pc->pc + 1) % MEM_SIZE)) % 256;
	ft_putchar(reg_content);
	pc += ((1 + 1) % MEM_SIZE); //OCP para que?
}


