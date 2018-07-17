/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:34:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/14 09:06:31 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void 	init_func(t_data *data)
{
	// (data->func)[0] = core_live;
	// (data->func)[10] = core_sti; //Usar a la macro de la posicion!!!!
	// (data->func)[8] = core_zjmp;
	// (data->func)[1] = core_ld;
	// (data->func)[2] = core_st;
	// (data->func)[3] = core_add;
	// (data->func)[5] = core_and;
	// (data->func)[11] = core_fork;
	
}

static void 	init_op(t_data *data)
{
	data->op[0] = (t_op){"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0};
	data->op[1] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	data->op[2] = (t_op){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	data->op[3] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0};
	data->op[4] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0};
	data->op[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	data->op[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	data->op[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	data->op[8] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	data->op[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1};
	data->op[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1};
	data->op[11] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	data->op[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0};
	data->op[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1};
	data->op[14] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	data->op[15] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
	data->op[16] = (t_op){0, 0, {0}, 0, 0, 0, 0, 0};
}


static int init_players(t_data *data)
{
	unsigned int i;

	if (!(data->players = (t_player *)ft_memalloc(sizeof(t_player) * data->n_players)))
		return (0);
	i = 0;
	while (i < data->n_players)
	{
		data->players[i] = (t_player){{0}, 0, 0, NULL, NULL,  i + 1, i + 1, 0, NULL, NULL, 1, NULL};
		if (!(data->players[i].pc = (t_pc *)malloc(sizeof(t_pc) * PC_BUFF)))
			ft_error("malloc failed");
		data->players[i].pc[0] = (t_pc){0, 0, 0};
		i++;
	}
	return (1);

}

static int init_arena(t_data *data)
{
	if (!(data->arena = (t_arena *)ft_memalloc(sizeof(t_arena))))
		return (0);
	return (1);

}

int 	init_corewar(t_data *data)
{
	if (!init_arena(data))
		return (0);
	if (!init_players(data))
		return (0);
	init_op(data);
	init_func(data);
	return (1);
}
