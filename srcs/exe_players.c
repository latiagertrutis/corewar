/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/09/10 17:05:19 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char op_nb;

	op_nb = (arena->board[pc->pc % MEM_SIZE].mem) - 1;
	if (pc->wait_cycles > 1)
	{
		pc->wait_cycles--;
		return ;
	}
	else if (pc->wait_cycles == 1)
	{
		pc->wait_cycles--;
//		ft_printf("executing.. %d\n", op_nb);
			// data->func[op_nb](player, pc, arena, data);
			data->func[pc->op](pc, arena, data);
	}
	else
	{
		if (op_nb <= 15)
		{
			pc->wait_cycles = (data->op[op_nb].mana) - 1;
			pc->op = op_nb;
		}
		else
			pc->pc = (pc->pc + 1) % MEM_SIZE;
	}
}

void 				exe_players(t_data *data)
{
	unsigned int k;
	unsigned int t;

	data->i = 0;
	fill_r1(data);
	while(data->cycle_to_die > 0)
	{
		t = 0;
		while (t < data->cycle_to_die)
		{
			k = data->nb_pc;
			while (k)
			{
				if (data->pc[k - 1].active)
					exe_pc((data->pc) + k - 1, data->arena, data); //TODO ejecutamos el turno cycle to die
				k--;
			}
			t++;
			data->nb_cycles++;
		}
		check_live_count(data);
	}
	check_winner(data->players, data->n_players);
}
