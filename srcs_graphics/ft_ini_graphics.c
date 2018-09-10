/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:20:16 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/10 15:16:10 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "corewar.h"

static t_sdl	*ini_graph(void)
{
	t_sdl *Graph;
	
	if (!(Graph = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_error("Error malloc ft_ini_graphics\n");
	Graph->screen.w = SCREEN_W;
	Graph->screen.h = SCREEN_H;
	Graph->screen.name = SCREEN_NAME;
	return (Graph);
}
static void	prepare_all(t_data *data, t_sdl **Graph)
{
	ft_ini_interface(*Graph, data);
	ft_ini_font(*Graph);
	ft_ini_information(data);
}

void ft_ini_graphics(t_sdl **Graph, t_mods *mods, t_data *data)
{
	int imgflags;

	*Graph = ini_graph();
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_SDL_error("SDL_Init", MODE_SDL);
	if (TTF_Init())	
		ft_SDL_error("SDL_Init", MODE_TTF);
	imgflags = IMG_INIT_JPG;
	if (!(IMG_Init(imgflags) & imgflags))
		ft_SDL_error("IMG_Init", MODE_IMG);
	if (!((*Graph)->screen.window = SDL_CreateWindow((*Graph)->screen.name,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (*Graph)->screen.w,
			(*Graph)->screen.h, SDL_WINDOW_RESIZABLE)))
		ft_SDL_error("SDL_CreateWindow", MODE_SDL);
	if (mods->fullscreen && SDL_SetWindowFullscreen((*Graph)->screen.window,
			SDL_WINDOW_FULLSCREEN_DESKTOP))
		ft_SDL_error("SDL_SetWindowFullscreen", MODE_SDL);
	SDL_GetWindowSize((*Graph)->screen.window, &((*Graph)->screen.w),
			&((*Graph)->screen.h));
	if (!((*Graph)->screen.Renderer = SDL_CreateRenderer((*Graph)->screen.window,
			-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_SDL_error("SDL_CreateRenderer", MODE_SDL);
	ft_printf("La ventana es %i x %i\n", (*Graph)->screen.w, (*Graph)->screen.h);
	if (SDL_SetRenderDrawColor((*Graph)->screen.Renderer, 0, 0, 0, 0))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	prepare_all(data, Graph);
}
