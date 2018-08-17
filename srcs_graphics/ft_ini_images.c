/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 10:50:58 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/17 12:51:47 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Surface		*prepare_hall(t_sdl *Graph)
{
	SDL_Surface *hall;
	SDL_Surface	*new_hall;
	SDL_RWops	*rwop;

	rwop = SDL_RWFromFile("./images/solo_hall.jpeg", "rb");
	if (!(hall = IMG_LoadJPG_RW(rwop)))
		ft_SDL_error("IMG_LoadJPH_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_SDL_error("SDL_RWclose", MODE_SDL);
	ft_printf("La zona mide %i x %i y la imagen %i x %i\n", Graph->square_info->w, Graph->big_square->h, hall->w, hall->h);
	new_hall = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w - Graph->player_nbr->w * 21,
			Graph->big_square->h, 32, 372645892);
	SDL_BlitScaled(hall, NULL, new_hall, NULL);
	SDL_FreeSurface(hall);
	return (new_hall);
}
static void	prepare_pauses(SDL_Surface *dst[2], t_sdl *Graph, char *image, int pos)
{
	SDL_Surface *pause;
	SDL_Surface	*new_pause;
	SDL_RWops	*rwop;

	rwop = SDL_RWFromFile(image, "rb");
	if (!(pause = IMG_LoadJPG_RW(rwop)))
		ft_SDL_error("IMG_LoadJPH_RW", MODE_IMG);
	if (SDL_RWclose(rwop))
		ft_SDL_error("SDL_RWclose", MODE_SDL);
	new_pause = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w - Graph->player_nbr->w * 21 - 22, 70, 32, 372645892);
	SDL_BlitScaled(pause, NULL, new_pause, NULL);
	SDL_FreeSurface(pause);
	dst[pos] = new_pause;
}

void	ft_ini_images(t_data *data, t_sdl *Graph)
{
	SDL_Surface *hall;
	int			i;
	char		*pixel;
	int			pitch;

	hall = prepare_hall(Graph);
	prepare_pauses(data->mods->pause_surf, Graph, "./images/pause_black.jpeg", 0);
	prepare_pauses(data->mods->pause_surf, Graph, "./images/pause_red.jpeg", 1);
	SDL_BlitSurface(data->mods->pause_surf[0], NULL, hall, &(SDL_Rect){12, 100, data->mods->pause_surf[0]->w, data->mods->pause_surf[0]->w});
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){Graph->square_info->w - hall->w, 0, hall->w, Graph->big_square->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(hall);
	i = -1;
	while (++i < Graph->big_square->h)
		memcpy(pixel + i * pitch, hall->pixels + i * hall->pitch, hall->pitch);
	SDL_UnlockSurface(hall);
	SDL_UnlockTexture(Graph->info_text);
}
