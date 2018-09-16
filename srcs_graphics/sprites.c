/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:28:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/16 02:07:42 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_ini_sprites(t_data *data, t_sdl *Graph)
{
	SDL_RWops *tmp;
	SDL_Surface *sprite;
	int disp_space_y;
	int disp_space_x;
	int i;

	if (!(Graph->heart = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * 7)))
		ft_error("malloc ft_ini_sprites");
	if (!(tmp = SDL_RWFromFile("./heart.png", "rb")))
		ft_SDL_error("SDL_RWFromFile", MODE_SDL);
	if (!(sprite = IMG_LoadPNG_RW(tmp)))
		ft_SDL_error("IMG_LoadPNG_RW", MODE_IMG);
//	if (!(Graph->heart[0] = (SDL_Surface *)ft_memalloc(sizeof(SDL_Surface))))
//		ft_error("malloc ft_ini_sprites 2");
	if (!(Graph->heart_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc ft_ini_sprites 2");
//	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, 76, 69, 32, 372645892);
//	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, 59, 52, 32, 372645892);
	i = 1; 
	disp_space_y = (Graph->info_marc->h - ((Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h) - (Graph->info_marc->y)));
	disp_space_x = Graph->player_nbr->w * 20;
	while (!Graph->heart[0] || (disp_space_y - Graph->heart[0]->h > 20 && Graph->heart[0]->h < disp_space_y && disp_space_x > Graph->heart[0]->w * 4))
	{
		if (Graph->heart[0])
			SDL_FreeSurface(Graph->heart[0]);
		Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
		SDL_FillRect(Graph->heart[0], NULL, 0xFF00FF00);
		SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, Graph->heart[0], NULL);
		i++;
	}
	i--;
	SDL_FreeSurface(Graph->heart[0]);
	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
//	SDL_FillRect(Graph->heart[0], NULL, 0xFF00FF00);
	SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, Graph->heart[0], NULL);
	*Graph->heart_pos = (SDL_Rect){Graph->info.cicles_play[0].x, ((Graph->info_marc->h - ((Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h) - (Graph->info_marc->y))) - Graph->heart[0]->h) / 2 + Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h, Graph->heart[0]->w, Graph->heart[0]->h};
//	if (SDL_BlitSurface(sprite, &(SDL_Rect){0, 0, 79, 72}, Graph->heart[0], NULL) < 0)
//		ft_SDL_error("SDL_BlitSurface", MODE_SDL);
//	Graph->heart[0] = sprite;
}

void	ft_check_health(t_data *data, t_sdl *Graph)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	int k;
	int t;

	t = 0;
	while(t < 4)
	{
		k = 0;
		while (k < 4)
		{
//		y_separation = Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h + Graph->heart[0]->h + (Graph->info_marc->h) * k++;
//	y_separation = Graph->square_info->h + 10 + (Graph->info_marc->h) * k++;
//		y_separation = ((Graph->info_marc->h - ((Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h) - (Graph->info_marc->y))) - Graph->heart[0]->h) / 2 + Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h;
			heart = (SDL_Rect){Graph->heart_pos->x + (Graph->heart_pos->w + (Graph->player_nbr->w * 20 - Graph->heart_pos->w * 4) / 3) * t, Graph->heart_pos->y + (Graph->info_marc->h) * k++, Graph->heart[0]->w, Graph->heart[0]->h};
			int j;
			SDL_LockTexture(Graph->info_text, &heart, (void **)&pixel, &pitch);
			SDL_LockSurface(Graph->heart[0]);
			j = 0;
			while (++j < Graph->heart[0]->h)
				memcpy(pixel + j * pitch, Graph->heart[0]->pixels + j * Graph->heart[0]->pitch, Graph->heart[0]->pitch);
			SDL_UnlockSurface(Graph->heart[0]);
			SDL_UnlockTexture(Graph->info_text);
		}
		t++;
	}
}

//hacer 4 corazones que ocupen toda la zona que hay entre los numeros de un jugador y el siguiente
