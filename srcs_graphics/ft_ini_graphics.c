/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:20:16 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/13 05:31:42 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/corewar.h"

void ft_ini_graphics(t_sdl *Game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_SDL_error("SDL_Init", MODE_SDL);
	if (TTF_Init())	
		ft_SDL_error("SDL_Init", MODE_TTF);
	if (!(Game->screen.window = SDL_CreateWindow(Game->screen.name,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game->screen.w,
			Game->screen.h, SDL_WINDOW_RESIZABLE)))
		ft_SDL_error("SDL_CreateWindow", MODE_SDL);
	if (ft_check_flags(Game->flags, 'f') &&
			SDL_SetWindowFullscreen(Game->screen.window,
			SDL_WINDOW_FULLSCREEN_DESKTOP))
		ft_SDL_error("SDL_SetWindowFullscreen", MODE_SDL);
	else
		SDL_GetWindowSize(Game->screen.window, &(Game->screen.w),
			&(Game->screen.h));
	if (!(Game->screen.Renderer = SDL_CreateRenderer(Game->screen.window,
			-1, SDL_RENDERER_SOFTWARE)))
		ft_SDL_error("SDL_CreateRenderer", MODE_SDL);
}
