/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 09:35:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_data *data, int j)
{
	unsigned int pos;

	pos = (data->arena->board[data->players[j].pc].mem) - 1;
	if (data->players[j].wait_cycles > 1)
	{
		data->players[j].wait_cycles--;
		return ;
	}
	else if (data->players[j].wait_cycles == 1)
	{
		data->players[j].wait_cycles--;
		data->func[pos](data->players + j, data->op[pos], data->arena);
	}
	else
	{
		if (pos == 0)
			data->players[j].wait_cycles += data->op[pos].mana;
		else
			data->players[j].pc++;
	}
}

void 				exe_players(t_data *data)
{
	int i;
	unsigned int j;
	SDL_Event	event;

	i = 0;
	fill_r1(data);

	print_board(data, data->arena->board);
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
//		usleep(100000);
		j = 0;
		while(j < data->n_players)
		{
			exe_pc(data, j);
			j++;
		}
		if (!(i % CYCLE_TO_DIE))
			check_live_count(data->players, data->n_players);
		i++;
		data->nb_cycles = i;
		write(1, "\x1b[H\x1b[2J", 7);
		print_board(data, data->arena->board);
		ft_board_to_screen(data->arena->Graph, data->arena, 0);
		ft_pcs_to_screen(data->arena->Graph, data->players, data->n_players, data->arena->board);
		SDL_RenderPresent(data->arena->Graph->screen.Renderer);

	}
}
