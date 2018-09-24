/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:17:54 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/24 17:29:58 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_func(t_op *ops)
{
	ops[0] = (t_op){core_live, 10};
	ops[1] = (t_op){core_ld, 5};
	ops[2] = (t_op){core_st, 5};
	ops[3] = (t_op){core_add, 10};
	ops[4] = (t_op){core_sub, 10};
	ops[5] = (t_op){core_and, 6};
	ops[6] = (t_op){core_or, 6};
	ops[7] = (t_op){core_xor, 6};
	ops[8] = (t_op){core_zjmp, 20};
	ops[9] = (t_op){core_ldi, 25};
	ops[10] = (t_op){core_sti, 25};
	ops[11] = (t_op){core_fork, 800};
	ops[12] = (t_op){core_lld, 10};
	ops[13] = (t_op){core_lldi, 50};
	ops[14] = (t_op){core_lfork, 100};
	ops[15] = (t_op){core_aff, 2};
}

static void	exe_pc(t_op *ops)
{
	t_pc			*aux_pc;
	unsigned char	op;
	unsigned int	wc;

	char			bool;

	aux_pc = g_pc;
	bool = 0;
	while (aux_pc)
	{
		wc = aux_pc->wait_cycles;
		if (wc == 0 && (op = g_mem[aux_pc->pc] - 1) < NB_INSTRUCTIONS)
		{
			aux_pc->wait_cycles = ops[op].cycles_wait;
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
			aux_pc->pc++;
		aux_pc = aux_pc->next;
	}
}

void		graphic_launch(const unsigned int flags)
{
	unsigned int 	i;
	t_op			ops[NB_INSTRUCTIONS];
//	pthread_t		thread;
//	void			*status;

	init_func(ops);
//	if ((pthread_create(&thread, NULL, print_board, NULL)))
//		ft_error("thread can not be created");
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
//	pthread_join(thread, &status);
}
