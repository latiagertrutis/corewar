/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycle_to_die.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:47:56 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/24 16:42:21 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	check_head(size_t *live_count)
{
	t_pc *aux_pc;

	while (g_pc && !g_pc->live)
	{
		ft_printf("El pc %u ha muerto.(CTD %d)\n", aux_pc->pc_num, g_cycle_to_die);
		aux_pc = g_pc->next;
		free(g_pc);
		g_pc = aux_pc;
		g_nb_pc--;
	}
	if (!g_pc)
		return(0);
	*live_count += g_pc->live;
	g_pc->live = 0;
	return (1);
}

static void	check_body(size_t *live_count)
{
	t_pc	*current_pc;
	t_pc	*previous_pc;
	t_pc	*next_pc;

	previous_pc = g_pc;
	current_pc = g_pc->next;
	while (current_pc)
	{
		if (current_pc->live)
		{
			*live_count += current_pc->live;
			current_pc->live = 0;
			current_pc = current_pc->next;
		}
		else
		{
			ft_printf("El pc %u ha muerto.(CTD %d)\n", current_pc->pc_num, g_cycle_to_die);
			next_pc = current_pc->next;
			previous_pc->next = next_pc;
			free(current_pc);
			current_pc = next_pc;
			g_nb_pc--;
		}
	}
}

void		check_cycle_to_die(void)
{
	size_t				live_count;
	static unsigned int checks = 0;

	if (!check_head(&live_count))
		return ;
	check_body(&live_count);
	if (live_count >= NBR_LIVE)
	{
		g_cycle_to_die -= CYCLE_DELTA;
		checks = 0;
	}
	else
	{
		checks++;
		if (checks == MAX_CHECKS)
		{
			g_cycle_to_die -= CYCLE_DELTA;
			checks = 0;
		}
	}
}
