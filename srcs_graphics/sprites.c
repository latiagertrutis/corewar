/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:28:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/13 17:36:33 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_ini_sprites(t_data *data, t_sdl *Graph)
{
	SDL_RWops *tmp;
	SDL_Surface *sprite;

	ft_printf("Voy a crear el sprite\n");
	if (!(Graph->heart = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * 7)))
		ft_error("malloc ft_ini_sprites");
	if (!(tmp = SDL_RWFromFile("./heart.png", "rb")))
		ft_SDL_error("SDL_RWFromFile", MODE_SDL);
	if (!(sprite = IMG_LoadPNG_RW(tmp)))
		ft_SDL_error("IMG_LoadPNG_RW", MODE_IMG);
	if (!(Graph->heart[0] = (SDL_Surface *)ft_memalloc(sizeof(SDL_Surface))))
		ft_error("malloc ft_ini_sprites 2");
//	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, 79, 72, 32, 372645892);
	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, 59, 52, 32, 372645892);
	SDL_FillRect(Graph->heart[0], NULL, 0xFF00FF00);
//	if (SDL_BlitSurface(sprite, &(SDL_Rect){0, 0, 79, 72}, Graph->heart[0], NULL) < 0)
//		ft_SDL_error("SDL_BlitSurface", MODE_SDL);
//	Graph->heart[0] = sprite;
	SDL_BlitScaled(sprite, &(SDL_Rect){0, 0, 79, 72}, Graph->heart[0], NULL);
	ft_printf("He creado el sprite\n");
}

void	ft_check_health(t_data *data, t_sdl *Graph)
{
	int pitch;
	char *pixel;

	int j;
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){0, 0, Graph->heart[0]->w, Graph->heart[0]->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(Graph->heart[0]);
	j = 0;
	while (++j < Graph->heart[0]->h)
		memcpy(pixel + j * pitch, Graph->heart[0]->pixels + j * Graph->heart[0]->pitch, Graph->heart[0]->pitch);
	SDL_UnlockSurface(Graph->heart[0]);
	SDL_UnlockTexture(Graph->info_text);
}

//hacer 4 corazones que ocupen toda la zona que hay entre los numeros de un jugador y el siguiente
