/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_launch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:27:14 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/28 17:20:48 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

static void	init_func(t_op *ops)
{
	ops[0] = (t_op){instruc_core_live, 10};
	ops[1] = (t_op){instruc_core_ld, 5};
	ops[2] = (t_op){instruc_core_st, 5};
	ops[3] = (t_op){instruc_core_add, 10};
	ops[4] = (t_op){instruc_core_sub, 10};
	ops[5] = (t_op){instruc_core_and, 6};
	ops[6] = (t_op){instruc_core_or, 6};
	ops[7] = (t_op){instruc_core_xor, 6};
	ops[8] = (t_op){instruc_core_zjmp, 20};
	ops[9] = (t_op){instruc_core_ldi, 25};
	ops[10] = (t_op){instruc_core_sti, 25};
	ops[11] = (t_op){instruc_core_fork, 800};
	ops[12] = (t_op){core_lld, 10};
	ops[13] = (t_op){core_lldi, 50};
	ops[14] = (t_op){core_lfork, 1000};
	ops[15] = (t_op){core_aff, 2};
}

static void	exe_pc(t_op *ops)
{
	t_pc			*aux_pc;
	unsigned char	op;
	unsigned int	wc;

	aux_pc = g_pc;
	while (aux_pc)
	{
		wc = aux_pc->wait_cycles;
		if (wc == 0 && (op = g_mem[aux_pc->pc] - 1) < NB_INSTRUCTIONS)
		{
			aux_pc->wait_cycles = ops[op].cycles_wait - 1;
			aux_pc->op = op;
		}
		else if (wc > 1)
			aux_pc->wait_cycles--;
		else if (wc == 1)
		{
			ops[aux_pc->op].func(aux_pc);
			aux_pc->wait_cycles--;
		}
		else
			aux_pc->pc = (aux_pc->pc + 1) % MEM_SIZE;
		aux_pc = aux_pc->next;
	}
	g_nb_cycles++;
}

static void	present_players (void)
{
	unsigned char i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < g_n_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", g_players[i].player_nb, g_players[i].prog_size,g_players[i].name, g_players[i].comment);
		i++;
	}
}

void		instruction_launch(void)
{
	int 	i;
	t_op			ops[NB_INSTRUCTIONS];

	init_func(ops);
	present_players();
	while (g_pc)
	{
		i = 0;
		while (i < g_cycle_to_die)
		{
			exe_pc(ops);
			i++;
		}
		check_cycle_to_die();
	}
}
