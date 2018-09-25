/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:47:26 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/25 20:54:14 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"


static void	move_frame(void)
{
	t_graphics *aux;

	aux = g_frame;
	pthread_mutex_lock(&g_lock);
	g_frame = g_frame->next;
	free(aux->pcs);
	free(aux);
	pthread_mutex_unlock(&g_lock);
}

static int			pause_button(unsigned int pause)
{
	SDL_Surface *button;
	int			i;
	char		*pixel;
	int			pitch;
	int			hall_dim;

	hall_dim = g_Graph->square_info->w - g_Graph->player_nbr->w * 21;
	if (pause)
		button = g_Graph->pause[0];
	else
		button = g_Graph->pause[1];
	SDL_LockTexture(g_Graph->info_text, &(SDL_Rect){g_Graph->square_info->w - hall_dim + (hall_dim - button->w) / 2, 100, button->w, button->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(button);
	i = -1;
	while (++i < button->h)
		memcpy(pixel + i * pitch, button->pixels + i * button->pitch, button->pitch);
	SDL_UnlockSurface(button);
	SDL_UnlockTexture(g_Graph->info_text);
	return (pause ? 0 : 0x1);
}

void		*graphic_thread(void *arg)
{
	unsigned int	flags;

	flags = *((unsigned int *)arg);
	ft_ini_graphics(flags);
	while (1)
	{
		if (g_frame && !g_pause)
		{
			if (g_frame->prog_end)
				break ;
			ft_board_to_screen(g_frame->board, flags);
			ft_update_info(g_frame->players, g_frame->cycle_pre_die);
			ft_set_back_to_front(flags);
			move_frame();
		}
	}
	ft_quit_graphics();
	return ((void *)NULL);
}
