/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:17:54 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/25 20:56:02 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"
#include "graphics.h"

t_sdl			*g_Graph;
t_graphics		*g_frame;
t_graphics		*g_graph_tail;
t_graphics		*g_aux;
pthread_mutex_t	g_lock;
unsigned int	g_pause;

static void	init_func(t_op *ops)
{
	ops[0] = (t_op){core_live, 10};
	ops[1] = (t_op){core_ld, 5};
	ops[2] = (t_op){graphics_core_st, 5};
	ops[3] = (t_op){core_add, 10};
	ops[4] = (t_op){core_sub, 10};
	ops[5] = (t_op){core_and, 6};
	ops[6] = (t_op){core_or, 6};
	ops[7] = (t_op){core_xor, 6};
	ops[8] = (t_op){core_zjmp, 20};
	ops[9] = (t_op){core_ldi, 25};
	ops[10] = (t_op){graphics_core_sti, 25};
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

static void	init_board(t_board *board)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	id;

	i = 0;
	id = 0;
	ft_memset(board, 0, sizeof(t_board) * MEM_SIZE);
	j = 0;
	while (j < MEM_SIZE)
	{
		i = 0;
		while (i < g_players[id].prog_size)
		{
			board[j].mem = g_mem[j];
			board[j].id = id + 1;
			i++;
			j++;
		}
		id++;
		j = id * (MEM_SIZE / g_n_players);
	}
}

static void	init_graph(void)
{
	unsigned int	i;
	t_pc			*aux_pc;

	if (!(g_aux = (t_graphics *)malloc(sizeof(t_graphics))))
		ft_error("malloc failed in init_graph");
	init_board(g_aux->board);
	ft_memcpy(g_aux->players, g_players, sizeof(t_player) * g_n_players);
	g_aux->cycle_to_die = g_cycle_to_die;
	g_aux->cycle_pre_die = 0;
	g_aux->cycle = g_nb_cycles;
	g_aux->nb_pc = g_nb_pc;
	if (!(g_aux->pcs = (unsigned int *)malloc(sizeof(unsigned int) * g_nb_pc)))
		ft_error("malloc failed in unit_graph");
	i = 0;
	aux_pc = g_pc;
	while (i < g_nb_pc)
	{
		g_aux->pcs[i] = (((unsigned int)aux_pc->id) << 24) | aux_pc->pc;
		i++;
	}
	g_aux->prog_end = 0x0;
	g_aux->next = NULL;
	g_graph_tail = g_aux;
	g_frame = g_aux;
	g_aux = NULL;
}

static void	fill_frame(int j)
{
	unsigned int i;
	t_pc			*aux_pc;

	ft_memcpy(g_aux->players, g_players, sizeof(t_player) * g_n_players);
	g_aux->cycle_to_die = g_cycle_to_die;
	g_aux->cycle_pre_die = j;
	g_aux->cycle = g_nb_cycles;
	g_aux->nb_pc = g_nb_pc;
	if (!(g_aux->pcs = (unsigned int *)malloc(sizeof(unsigned int) * g_nb_pc)))
		ft_error("malloc failed in unit_graph");
	i = 0;
	aux_pc = g_pc;
	while (i < g_nb_pc)
	{
		g_aux->pcs[i] = (((unsigned int)aux_pc->id) << 24) | aux_pc->pc;
		i++;
	}
}

static void	add_frame(void)
{
	pthread_mutex_lock(&g_lock);
	if (g_frame)
	{
		g_graph_tail->next = g_aux;
		g_graph_tail = g_graph_tail->next;
	}
	else
	{
		g_frame = g_aux;
		g_graph_tail = g_frame;
	}
	g_aux = NULL;
	pthread_mutex_unlock(&g_lock);
}

static void	end_frame(void)
{
	if (!(g_aux = (t_graphics *)malloc(sizeof(t_graphics))))
		ft_error("malloc failed in end_frame");
	g_aux->prog_end = 0x1;
	add_frame();
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

void		graphic_launch(const unsigned int flags)
{
	int 			i;
	t_op			ops[NB_INSTRUCTIONS];
	pthread_t		thread;
	void			*status;
	SDL_Event		event;
	int				running;

	running = 1;
	init_func(ops);
	init_graph();
	pthread_mutex_init(&g_lock, NULL);
	new_frame();
	g_pause = 0;
	if ((pthread_create(&thread, NULL, graphic_thread, (void *)(&flags))))
		ft_error("thread can not be created");
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = SDL_FALSE;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = SDL_FALSE;
				else if (event.key.keysym.sym == SDLK_SPACE)
					g_pause = pause_button(g_pause);
				/* else if (event.key.keysym.sym == SDLK_RIGHT) */
				/* 	data->mods->step = 1; */
				/* else if (event.key.keysym.sym == SDLK_i) */
				/* 	data->mods->info = data->mods->info ? 0 : 1; */
			}
		}
		if (g_pc)
		{
			i = 0;
			while (i < g_cycle_to_die)
			{
				new_frame();
				exe_pc(ops);
				fill_frame(i);
				add_frame();
				i++;
			}
			check_cycle_to_die();
		}
	}
	end_frame();
	pthread_mutex_destroy(&g_lock);
	pthread_join(thread, &status);
}
