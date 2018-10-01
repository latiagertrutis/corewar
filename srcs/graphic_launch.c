/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:17:54 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/10/01 20:29:59 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"
#include "graphics.h"

t_sdl			*g_graph;
t_graphics		*g_frame;
t_graphics		*g_graph_tail;
t_graphics		*g_aux;
pthread_mutex_t	g_lock;
unsigned int	g_pause;
unsigned int	g_hexl;
unsigned int	g_step;
t_board			g_board[MEM_SIZE];

static void			move_frame(void)
{
	t_graphics *aux;

	pthread_mutex_lock(&g_lock);
	aux = g_frame;
	g_frame = g_frame->next;
	free(aux->pcs);
	free(aux);
	pthread_mutex_unlock(&g_lock);
}

static int			pause_button(unsigned int pause)
{
	SDL_Surface *button;
	int			hall_dim;

	hall_dim = g_graph->square_info->w - g_graph->player_nbr->w * 21;
	if (pause)
		button = g_graph->pause[0];
	else
		button = g_graph->pause[1];
	ft_surf_to_text(g_graph->info_text, button,
		&(SDL_Rect){g_graph->square_info->w - hall_dim + (hall_dim - button->w)
		/ 2, 100, button->w, button->h});
	return (pause ? 0 : 0x1);
}

static void			events_bucle(int *running)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			*running = SDL_FALSE;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				*running = SDL_FALSE;
			else if (event.key.keysym.sym == SDLK_SPACE)
				g_pause = pause_button(g_pause);
			else if (event.key.keysym.sym == SDLK_RIGHT)
				g_step = 1;
			else if (event.key.keysym.sym == SDLK_i)
				g_hexl = g_hexl ? 0 : 1;
		}
	}
}

static void			graphic_main_bucle(const unsigned int flags)
{
	int			running;

	running = 1;
	while (running)
	{
		events_bucle(&running);
		if (g_frame)
		{
			if (g_frame->prog_end)
				break ;
			ft_board_to_screen(g_frame->board);
			ft_update_info(g_frame->players, g_frame->cycle_pre_die);
			ft_set_back_to_front(flags);
			if (!g_pause || g_step)
				move_frame();
			g_step = 0;
		}
	}
}

void				graphic_launch(const unsigned int flags)
{
	pthread_t		thread;
	void			*status;
	int				running;

	running = 1;
	pthread_mutex_init(&g_lock, NULL);
	g_pause = 0;
	g_hexl = 1;
	g_step = 0;
	if ((pthread_create(&thread, NULL, graphic_thread, (void *)NULL)))
		ft_error("thread can not be created");
	ft_ini_graphics(flags);
	graphic_main_bucle(flags);
	ft_quit_graphics();
	pthread_mutex_destroy(&g_lock);
	pthread_join(thread, &status);
}
