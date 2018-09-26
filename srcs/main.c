/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/09/16 17:07:49 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> //printf !!

static void		ini_mods(int flags, t_mods *mods)
{
//	if (!(mods = (t_mods *)ft_memalloc(sizeof(t_mods))))
//		ft_error("Error malloc ini_mods\n");
	mods->running = 0x1;
	if (ft_check_flags(flags, 'f'))
		mods->fullscreen = 0x1;
	if (ft_check_flags(flags, 'v'))
		mods->visual = 0x1;
	if (ft_check_flags(flags, 'd'))
	{
		mods->dump = 0x1;
		mods->info = 0x1;
	}
}

int main(int ac, char **av)
{
	t_data		data;
//	data = (t_data){0, CYCLE_TO_DIE, ac - 1, NULL, NULL, {"\033[0m", "\033[38;5;1m", "\033[38;5;2m",
//	   		"\033[38;5;3m", "\033[38;5;4m"}, {{0, 0, {0}, 0, 0, 0, 0, 0}}, 0, {0}};
//	if (ac < 2 || ac > 5)
//		put_usage();
	data = (t_data){0, 0, CYCLE_TO_DIE, 0, NULL, NULL, {"\033[0m", "\033[38;5;1m", "\033[38;5;2m",
		"\033[38;5;3m", "\033[38;5;4m"}, {{0, 0, {0}, 0, 0, 0, 0, 0}},
	                0, 0, 0, NULL, {0}, 0, 0, 0, 0, NULL}; //new anadido nb_pc y *pc al final
	if (!(data.pc = (t_pc *)ft_memalloc(sizeof(t_pc) * PC_BUFF)))
		ft_error("malloc failed");
//	data.pc[0] = (t_pc){0, 0, 0, {{0}}, 0};

	data.flags = ft_set_flags(ac, av, &data);


	ini_mods(data.flags, data.mods);

	ft_printf("Voy a inicializar todo\n");
	if (!init_corewar(&data, ac, av))
		ft_error("malloc failed");
	ft_printf("todo inicializado\n");

	// ft_putnbr(data.n_players);
	// exit(1);

	put_champs_to_arena(&data);

//	ft_ini_interface(data.arena->Graph);
//	ft_ini_font(data.arena->Graph);
//	SDL_GetRendererInfo(data.arena->Graph->screen.Renderer, &info);
//	ft_printf("Name = %s\nflags = %x\nnum texture formats = %x\ntexture formats[0]] = \t%b\nsizeof SDL_Surface %i\n", info.name, info.flags, info.num_texture_formats, info.texture_formats[0], sizeof(SDL_Surface));
//	SDL_RenderPresent(data.arena->Graph->screen.Renderer);

//	ft_quit_graphics(data.arena->Graph);
	ft_printf("voy a empezar\n");
	if (data.mods->visual && !data.mods->dump)
		exe_players_interf(&data);
	else if (data.mods->dump)
		exe_players_dump(&data);
	else
		exe_players(&data);
	if (data.mods->visual)
		ft_quit_graphics(data.arena->Graph);
	free(data.arena);
	free_players(data.players, data.n_players);
	return (0);
}

//4 Empezar con las intrucciones: Mateo pares, Mikel impares
