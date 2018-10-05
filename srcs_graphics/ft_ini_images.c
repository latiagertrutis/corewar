/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 10:50:58 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/05 21:01:09 by jagarcia         ###   ########.fr       */
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
	SDL_RWops	*rwop;
	int			hall_dim;

	hall_dim = g_graph->square_info->w - g_graph->player_nbr->w * 21;
	if (!(rwop = SDL_RWFromFile(image, "rb")))
		ft_sdl_error("SDL_RWFromFile", MODE_SDL);
	if (!(pause = IMG_LoadPNG_RW(rwop)))
		ft_sdl_error("IMG_LoadPNG_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_sdl_error("SDL_RWclose", MODE_SDL);
	if (!(dst[pos] = SDL_CreateRGBSurfaceWithFormat(0, g_graph->square_info->w
		- g_graph->player_nbr->w * 21 - 70, g_graph->square_info->w
		- g_graph->player_nbr->w * 21 - 70, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (SDL_BlitScaled(pause, NULL, dst[pos], NULL))
		ft_sdl_error("SDL_BlitScaled", MODE_SDL);
	if (!(g_graph->pause_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc prepare_pauses");
	*g_graph->pause_pos = (SDL_Rect){g_graph->square_info->w - hall_dim +
		(hall_dim - dst[pos]->w) / 2, 
		100, dst[pos]->w, dst[pos]->h};
	SDL_FreeSurface(pause);
}

static void		prepare_screen()
{
	SDL_RWops	*rwop;
	SDL_Surface	*screen;

	if (!(rwop = SDL_RWFromFile("./images/screen.png", "rb")))
		ft_sdl_error("SDL_RWFromFile", MODE_SDL);
	if (!(screen = IMG_LoadPNG_RW(rwop)))
		ft_sdl_error("IMG_LoadPNG_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_sdl_error("SDL_RWclose", MODE_SDL);
	if (!(g_graph->little_screen = SDL_CreateRGBSurfaceWithFormat(0,
		g_graph->pause_pos->w, g_graph->pause_pos->h, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (SDL_BlitScaled(screen, NULL, g_graph->little_screen, NULL))
		ft_sdl_error("SDL_BlitScaled", MODE_SDL);
	SDL_FreeSurface(screen);
	if (!(g_graph->little_screen_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc prepare_screen");
	*g_graph->little_screen_pos = (SDL_Rect){g_graph->pause_pos->x,
		g_graph->pause_pos->y + g_graph->pause_pos->h + 5,
		g_graph->little_screen->w, g_graph->little_screen->h};
}

static void			prepare_screen_buttons(SDL_Surface *dst[4], char *file,
		int pos)
{
	SDL_RWops *rwop;
	SDL_Surface *button;
	SDL_Surface *tmp;
	
	if (!(rwop = SDL_RWFromFile(file, "rb")))
		ft_sdl_error("SDL_RWFromFile", MODE_SDL);
	if (!(button = IMG_LoadPNG_RW(rwop)))
		ft_sdl_error("IMG_LoadPNG_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_sdl_error("SDL_RWclose", MODE_SDL);
	if (!(dst[pos] = SDL_CreateRGBSurfaceWithFormat(0, g_graph->little_screen->w / 2, 50, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (!(tmp = SDL_ConvertSurfaceFormat(button, dst[pos]->format->format, 0)))
		ft_sdl_error("SDL_ConvertSurfaceFormat", MODE_SDL);
	if (SDL_BlitScaled(tmp, NULL, dst[pos], NULL))
		ft_sdl_error("SDL_BlitScaled", MODE_SDL);
	if (!(g_graph->button_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc prepare_screen_buttons");
	*g_graph->button_pos = (SDL_Rect){g_graph->little_screen_pos->x, g_graph->little_screen_pos->y + g_graph->little_screen_pos->h, dst[pos]->w, dst[pos]->h};
	SDL_FreeSurface(tmp);
	SDL_FreeSurface(button);
}

void				ft_ini_images(void)
{
	SDL_Surface *hall;

	hall = prepare_hall();
	prepare_pauses(g_graph->pause, "./images/hall_on.png", 0);
	prepare_pauses(g_graph->pause, "./images/hall_off.png", 1);
	prepare_screen();
	prepare_screen_buttons(g_graph->plus_minus, "./images/backwards.png", 1);
	prepare_screen_buttons(g_graph->plus_minus, "./images/backwards_push.png", 0);
	prepare_screen_buttons(g_graph->plus_minus, "./images/forward.png", 3);
	prepare_screen_buttons(g_graph->plus_minus, "./images/forward_push.png", 2);
	if (SDL_BlitSurface(g_graph->pause[1], NULL, hall, &(SDL_Rect){(hall->w
		- g_graph->pause[0]->w) / 2, 100, g_graph->pause[0]->w,
		g_graph->pause[0]->w}))
		ft_sdl_error("SDL_BlitSurface", MODE_SDL);
	if (SDL_BlitSurface(g_graph->little_screen, NULL, hall, &(SDL_Rect){(hall->w
		- g_graph->little_screen->w) / 2, 100 + g_graph->pause_pos->h + 5,
		g_graph->little_screen->w, g_graph->little_screen->h}))		
		ft_sdl_error("SDL_BlitSurface", MODE_SDL);
	if (SDL_BlitSurface(g_graph->plus_minus[0], NULL, hall, &(SDL_Rect){(hall->w
		- g_graph->little_screen->w) / 2, 100 + g_graph->pause_pos->h + 5 + g_graph->little_screen->h,
		g_graph->little_screen->w, g_graph->little_screen->h}))
		ft_sdl_error("SDL_BlitSurface", MODE_SDL);
	if (SDL_BlitSurface(g_graph->plus_minus[2], NULL, hall, &(SDL_Rect){(hall->w
		- g_graph->little_screen->w) / 2 + g_graph->button_pos->w, 100 + g_graph->pause_pos->h + 5 + g_graph->little_screen->h,
					g_graph->little_screen->w, g_graph->little_screen->h}))
		ft_sdl_error("SDL_BlitSurface", MODE_SDL);
	ft_surf_to_text(g_graph->info_text, hall,
		&(SDL_Rect){g_graph->square_info->w - hall->w, 0,
		hall->w, g_graph->big_square->h});
}
