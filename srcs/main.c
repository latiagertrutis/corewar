/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/14 11:08:16 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> //printf !!

int main(int ac, char **av)
{
	t_data		data;
	SDL_Event	event;

//	if (ac < 2 || ac > 5)
//		put_usage();
	data = (t_data){1, NULL, NULL, {"\033[0m", "\033[38;5;1m", "\033[38;5;2m",
		"\033[38;5;3m", "\033[38;5;4m"}, {{0, 0, {0}, 0, 0, 0, 0, 0}},
		0, 0, {0}};
	data.flags = ft_set_flags(ac, av);
	if (!init_corewar(&data))
		ft_error("malloc failed");
	take_champions(&data, av);
	ft_ini_interface(data.arena->Graph);
	ft_ini_board(data.arena->Graph);
//	put_champs_to_arena(&data);

while (data.arena->Graph->running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				data.arena->Graph->running = SDL_FALSE;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					data.arena->Graph->running = SDL_FALSE;
			}
		}
	}

//	exe_players(&data);

	ft_quit_graphics(data.arena->Graph);
	free(data.arena);
	free_players(data.players, data.n_players);
	return (0);
}

//4 Empezar con las intrucciones: Mateo pares, Mikel impares
