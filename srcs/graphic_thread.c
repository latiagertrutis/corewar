/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:47:26 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/24 22:44:53 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"


static void	move_frame(void)
{
	t_graphics *aux;

	aux = g_frame;
	g_frame = g_frame->next;
	free(aux->pcs);
	free(aux);
}

void		*graphic_thread(void *arg)
{
	char			running;
	unsigned int	flags;

	running = 1;
	flags = (unsigned int)arg;
	ft_ini_graphics(flags);
	while (running)
	{
		if (g_frame)
		{
			ft_board_to_screen(g_frame->board, flags);
			ft_update_info(g_frame->players, g_frame->cycle_pre_die);
			ft_set_back_to_front(flags);
			if (g_frame->prog_end)
				running = 0;
			move_frame();
		}
	}
	ft_quit_graphics();
	return ((void *)NULL);
}
