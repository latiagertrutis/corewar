/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/21 20:43:06 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> //printf !!

int main(int ac, char **av)
{
	t_data		data;
	SDL_RendererInfo	info;

//	if (ac < 2 || ac > 5)
//		put_usage();
	data = (t_data){3, NULL, NULL, {"\033[0m", "\033[38;5;1m", "\033[38;5;2m",
		"\033[38;5;3m", "\033[38;5;4m"}, {{0, 0, {0}, 0, 0, 0, 0, 0}},
	                0, 0, 0, {0}};
	data.flags = ft_set_flags(ac, av);
	if (!init_corewar(&data))
		ft_error("malloc failed");
	take_champions(&data, av);
	put_champs_to_arena(&data);
	ft_ini_interface(data.arena->Graph);
	ft_ini_font(data.arena->Graph);
	SDL_GetRendererInfo(data.arena->Graph->screen.Renderer, &info);
	ft_printf("Name = %s\nflags = %x\nnum texture formats = %x\ntexture formats[0]] = \t%b\nsizeof SDL_Surface %i\n", info.name, info.flags, info.num_texture_formats, info.texture_formats[0], sizeof(SDL_Surface));
	SDL_RenderPresent(data.arena->Graph->screen.Renderer);
	exe_players(&data);
	ft_quit_graphics(data.arena->Graph);
	free(data.arena);
	free_players(data.players, data.n_players);
	return (0);
}

//4 Empezar con las intrucciones: Mateo pares, Mikel impares
