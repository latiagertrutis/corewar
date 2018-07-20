/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/20 13:22:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_player *player, t_pc *pc, t_arena *arena, t_data *data)
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
		data->func[op_nb](player, pc, arena);
	}
	else
	{
		// if (pos <= 3 || || pos == 5 || pos == 10 || pos == 8)
		if (op_nb < 14)
			pc->wait_cycles += (data->op[op_nb].mana) + 1;
		else
			pc->pc = (pc->pc + 1) % MEM_SIZE;
	}
}

static void			set_back_to_front(t_sdl *Graph, SDL_Surface *surf)
{
	SDL_Texture *texture;

	if (!(texture = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf)))
		ft_SDL_error("SDL_CreateTextureFromSurface", MODE_SDL);
	SDL_RenderCopy(Graph->screen.Renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(Graph->screen.Renderer);
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, BACK_COLOR
	SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	SDL_RenderClear(Graph->screen.Renderer);
}

void 				exe_players(t_data *data)
{
	unsigned int j;
	SDL_Event	event;
	unsigned int k;	

	data->i = 0;
	fill_r1(data);
	while (data->arena->Graph->running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				data->arena->Graph->running = SDL_FALSE;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					data->arena->Graph->running = SDL_FALSE;
			}
		}
		j = 0;
		while(j < data->n_players)
		{
			k = 0;
			while (k < data->players[j].nb_pc)
			{
				exe_pc((data->players) + j, (data->players[j].pc) + k, data->arena, data);
				k++;
			}
			j++;
		}
		if (!(data->i % CYCLE_TO_DIE))
			check_live_count(data->players, data->n_players);
		data->i++;
		data->nb_cycles = data->i;
		ft_draw_rack(data, data->arena->Graph->screen.screen);
		ft_board_to_screen(data->arena->Graph, data->arena);
		ft_pcs_to_screen(data, data->arena->Graph, data->players);
		set_back_to_front(data->arena->Graph, data->arena->Graph->screen.screen);
//		if (data->i == 100)
//			data->arena->Graph->running = 0;
	}
}
