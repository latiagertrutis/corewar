/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/24 18:47:31 by jagarcia         ###   ########.fr       */
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



void 				exe_players(t_data *data)
{
	unsigned int j;
	unsigned int k;
	unsigned int t;
	unsigned int pause;
	unsigned int step;
	SDL_Event	event;

	pause = 1;
	step = 0;
	data->i = 0;
	
	fill_r1(data);
//	print_board(data, data->arena->board);
	while(data->nb_cycles < 500000 && data->mods->running)
	{
		t = 0;
		while (t < data->cycle_to_die && data->mods->running)
		{
			while (SDL_PollEvent(&event) && data->mods->visual)
			{
				if (event.type == SDL_QUIT)
					data->mods->running = 0;
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
						data->mods->running = SDL_FALSE;
					else if (event.key.keysym.sym == SDLK_SPACE)
						pause = pause ? 0 : 1;
					else if (event.key.keysym.sym == SDLK_RIGHT)
						step = 1;
				}
				else if (event.type == SDL_KEYUP)
					if (event.key.keysym.sym == SDLK_RIGHT)
						step = 0;
			}
			// usleep(100);
			if (pause || step)
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
//				write(1, "\x1b[H\x1b[2J", 7);
//				print_board(data, data->arena->board);
//				if (!(data->i % CYCLE_TO_DIE))
//					check_live_count(data->players, data->n_players);
				data->i++;
				data->nb_cycles++;
				if (data->mods->visual)
				{
					ft_board_to_screen(data->arena->Graph, data->arena->board, data);
					ft_set_back_to_front(data->arena->Graph);
				}
//				if (data->i == 100)
//					exit(1);
//				pause = 0;
			}
		}
		check_live_count(data->players, data->n_players);
		data->cycle_to_die -= CYCLE_DELTA;
	}
}
