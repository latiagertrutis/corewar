/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_data_surfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:02:57 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/01 10:26:17 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ini_number(t_sdl *Graph, int mode, SDL_Surface **number,
		SDL_Rect square_info)
{
	*number = SDL_CreateRGBSurfaceWithFormat(0, square_info.w, square_info.h,
			32, Graph->rack->format->format);
	SDL_FillRect(*number, NULL, SDL_MapRGBA(Graph->rack->format, 255, 255, 255,
			255));
	SDL_FillRect(*number, &(SDL_Rect){1, 1, (*number)->w - 2, (*number)->h - 2},
			SDL_MapRGBA((*number)->format, 0, 0, 0, 255));
	while (Graph->font[mode].w + 10 < (*number)->w && Graph->font[mode].h +
			10 < (*number)->h)
	{
		if (Graph->font[mode].font)
			TTF_CloseFont(Graph->font[mode].font);
		if (!(Graph->font[mode].font = TTF_OpenFont("./whitrabt.ttf",
				++Graph->font[mode].font_size)))
			ft_SDL_error("TTF_OpenFont", MODE_TTF);
		TTF_SizeUTF8(Graph->font[mode].font, "0", &Graph->font[mode].w,
				&Graph->font[mode].h);
	}
}

static void		ini_info_rects(t_sdl *Graph)
{
	Graph->info.cicles_gen = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	*Graph->info.cicles_gen = (SDL_Rect){0, 0, Graph->square_info->w / 20,
			Graph->square_info->h / 6};
	Graph->info.cicle_to_die = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	*Graph->info.cicle_to_die = *Graph->info.cicles_gen;
	Graph->info.processos = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	*Graph->info.processos = *Graph->info.cicles_gen;
}

void	ft_ini_material(t_data *data, t_sdl *Graph, SDL_Surface *info_marc)
{
	int i;

	ini_info_rects(Graph);
	ini_number(Graph, GENERAL_NBR_FONT, &Graph->general_nbr,
			*Graph->info.cicles_gen);
	ft_put_general_info(Graph);
	Graph->info.cicles_play = (SDL_Rect *)malloc(sizeof(SDL_Rect) *
			data->n_players);
	Graph->info.lst_life = (SDL_Rect *)malloc(sizeof(SDL_Rect) *
			data->n_players);
	ini_number(Graph, PLAYER_NBR_FONT, &Graph->player_nbr,
			(SDL_Rect){0, 0, info_marc->w / 30, info_marc->h / 6});
	i = 0;
	while (i < data->n_players)
	{
		Graph->info.cicles_play[i] = (SDL_Rect){0, 0, info_marc->w / 30,
				info_marc->h / 6};
		Graph->info.lst_life[i] = (SDL_Rect){0, 0, info_marc->w / 30,
				info_marc->h / 6};
		ft_put_player_info(Graph, info_marc, data, i++);
	}
}
