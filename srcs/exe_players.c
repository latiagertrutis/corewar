/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/23 13:45:55 by jagarcia         ###   ########.fr       */
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
		ft_printf("ejecutando %d\n", op_nb);
		if (op_nb <= 15)
			data->func[op_nb](player, pc, arena);
	}
	else
	{
		if (op_nb <= 15)
			pc->wait_cycles += (data->op[op_nb].mana) + 1;
		else
			pc->pc = (pc->pc + 1) % MEM_SIZE;
	}
}

static void				test(t_sdl *Graph)
{
	SDL_Surface *surf;
	SDL_Texture *text;

	surf = TTF_RenderUTF8_Blended(Graph->font_info.font, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", (SDL_Color){255, 255, 0, 0});
	text = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf);
//	SDL_SetRenderTarget(Graph->screen.Renderer, Graph->screen.texture);
	SDL_RenderCopy(Graph->screen.Renderer, text, NULL, &(SDL_Rect){100, 50, surf->w, surf->h});
}

static void			set_back_to_front(t_sdl *Graph, SDL_Surface *surf)
{
	SDL_Texture *texture;
	Uint32	format;
	int		*pixels_tex;
	int		pitch;

//	if (!(texture = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf)))
//		ft_SDL_error("SDL_CreateTextureFromSurface", MODE_SDL);
	
//	SDL_LockTexture(Graph->screen.texture, NULL, (void **)&pixels_tex, &pitch);
//	SDL_LockSurface(Graph->screen.screen);
//	memcpy(pixels_tex, Graph->screen.screen->pixels, Graph->screen.screen->w * Graph->screen.screen->h * 4);
//	SDL_UnlockSurface(Graph->screen.screen);
//	SDL_UnlockTexture(Graph->screen.texture);
//	ft_printf("format2 screen_surf \t%b\n",surf->format->format);
//	SDL_QueryTexture(Graph->screen.texture, &format, NULL, NULL, NULL);
//	ft_printf("format3 texture \t%b\n",format);
	
	SDL_RenderCopy(Graph->screen.Renderer, Graph->screen.texture, NULL, Graph->big_square);
//	SDL_DestroyTexture(texture);
//	usleep(5000);
//	test(Graph);
	SDL_RenderPresent(Graph->screen.Renderer);
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, BACK_COLOR SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
//	SDL_SetRenderTarget(Graph->screen.Renderer, Graph->screen.texture);
	SDL_RenderClear(Graph->screen.Renderer);
//	SDL_LockTexture(Graph->screen.texture, NULL, (void **)&pixels_tex, &pitch);
//	SDL_LockSurface(Graph->screen.screen);
//	for (int j = 0; j < Graph->screen.h * pitch / 4; j++)
//		pixels_tex[j] = 0xFF1C1C15;
//	SDL_UnlockSurface(Graph->screen.screen);
//	SDL_UnlockTexture(Graph->screen.texture);
}



void 				exe_players(t_data *data)
{
	unsigned int j;
	unsigned int k;
	unsigned int t;
	unsigned int pause;
	SDL_Event	event;

	pause = 1;
	data->i = 0;
	fill_r1(data);
//	print_board(data, data->arena->board);
	while(data->nb_cycles < 500000 && data->arena->Graph->running)
	{
		t = 0;
		while (t < data->cycle_to_die && data->arena->Graph->running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					data->arena->Graph->running = SDL_FALSE;
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
						data->arena->Graph->running = SDL_FALSE;
					if (event.key.keysym.sym == SDLK_SPACE)
						pause = pause ? 0 : 1;
				}
			}
			// usleep(100);
			if (pause)
			{
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
			t++;
//			write(1, "\x1b[H\x1b[2J", 7);
//			print_board(data, data->arena->board);
//			if (!(data->i % CYCLE_TO_DIE))
//				check_live_count(data->players, data->n_players);
			data->i++;
			data->nb_cycles++;
			ft_board_to_screen(data->arena->Graph, data->arena);
			ft_draw_rack(data, data->arena->Graph->screen.screen);
			ft_pcs_to_screen(data, data->arena->Graph, data->players);
			set_back_to_front(data->arena->Graph, data->arena->Graph->screen.screen);
//			if (data->i == 100)
//				exit(1);
			}
		}
		check_live_count(data->players, data->n_players);
		data->cycle_to_die -= CYCLE_DELTA;
	}
}
