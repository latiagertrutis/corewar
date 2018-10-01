/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 10:50:58 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/01 19:50:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static SDL_Surface	*prepare_hall(void)
{
	SDL_Surface *hall;
	SDL_Surface	*new_hall;
	SDL_RWops	*rwop;

	if (!(rwop = SDL_RWFromFile("./images/solo_hall.jpeg", "rb")))
		ft_sdl_error("SDL_RWFromFile", MODE_SDL);
	if (!(hall = IMG_LoadJPG_RW(rwop)))
		ft_sdl_error("IMG_LoadJPH_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_sdl_error("SDL_RWclose", MODE_SDL);
	if (!(new_hall = SDL_CreateRGBSurfaceWithFormat(0, g_graph->square_info->w
		- g_graph->player_nbr->w * 21, g_graph->big_square->h, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (SDL_BlitScaled(hall, NULL, new_hall, NULL))
		ft_sdl_error("SDL_BlitScaled", MODE_SDL);
	SDL_FreeSurface(hall);
	return (new_hall);
}

static void			prepare_pauses(SDL_Surface *dst[2], char *image, int pos)
{
	SDL_Surface *pause;
	SDL_Surface	*new_pause;
	SDL_RWops	*rwop;

	if (!(rwop = SDL_RWFromFile(image, "rb")))
		ft_sdl_error("SDL_RWFromFile", MODE_SDL);
	if (!(pause = IMG_LoadJPG_RW(rwop)))
		ft_sdl_error("IMG_LoadJPH_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_sdl_error("SDL_RWclose", MODE_SDL);
	if (!(new_pause = SDL_CreateRGBSurfaceWithFormat(0, g_graph->square_info->w
		- g_graph->player_nbr->w * 21 - 70, 40, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (SDL_BlitScaled(pause, NULL, new_pause, NULL))
		ft_sdl_error("SDL_BlitScaled", MODE_SDL);
	SDL_FreeSurface(pause);
	dst[pos] = new_pause;
}

void				ft_ini_images(void)
{
	SDL_Surface *hall;

	hall = prepare_hall();
	prepare_pauses(g_graph->pause, "./images/pause_black.jpeg", 0);
	prepare_pauses(g_graph->pause, "./images/pause_red.jpeg", 1);
	if (SDL_BlitSurface(g_graph->pause[0], NULL, hall, &(SDL_Rect){(hall->w
		- g_graph->pause[0]->w) / 2, 100, g_graph->pause[0]->w,
		g_graph->pause[0]->w}))
		ft_sdl_error("SDL_BlitSurface", MODE_SDL);
	ft_surf_to_text(g_graph->info_text, hall,
		&(SDL_Rect){g_graph->square_info->w - hall->w, 0,
		hall->w, g_graph->big_square->h});
}
