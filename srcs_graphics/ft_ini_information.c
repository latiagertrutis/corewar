/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_information.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 03:49:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/25 23:20:25 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static Uint32	take_color_player(int i, SDL_PixelFormat *format)
{
	if (!i)
		return (SDL_MapRGBA(format, 51, 255, 51, SDL_ALPHA_OPAQUE));
	else if (i == 1)
		return (SDL_MapRGBA(format, 255, 204, 0, SDL_ALPHA_OPAQUE));
	else if (i == 2)
		return (SDL_MapRGBA(format, 255, 242, 207, SDL_ALPHA_OPAQUE));
	else if (i == 3)
		return (SDL_MapRGBA(format, 252, 102, 92, SDL_ALPHA_OPAQUE));
	else if (i == 4)
		return (SDL_MapRGBA(format, FIELD_COLOR SDL_ALPHA_OPAQUE));
	else
		return (SDL_MapRGBA(format, 0, 0, 0, SDL_ALPHA_OPAQUE));

}

static void		ini_general(t_sdl *Graph)
{
	SDL_Surface *info_marc;
	int			i;
	char		*pixel;
	int			pitch;
	
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w,
		Graph->square_info->h, 32, 372645892);
	SDL_FillRect(info_marc, NULL, take_color_player(4, info_marc->format));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
		info_marc->h - 10}, SDL_MapRGBA(info_marc->format, 0, 0, 0,
		SDL_ALPHA_OPAQUE));
	SDL_LockTexture(Graph->info_text, Graph->square_info,
		(void **)&pixel, &pitch);
	SDL_LockSurface(info_marc);
	i = -1;
	while (++i < info_marc->h)
		memcpy(pixel + i * pitch, info_marc->pixels + i * info_marc->pitch,
			info_marc->pitch);
	SDL_UnlockSurface(info_marc);
	SDL_UnlockTexture(Graph->info_text);
	SDL_FreeSurface(info_marc);
}

static void		ini_player(t_sdl *Graph, int i, SDL_Surface *info_marc)
{
	char	*pixel;
	int		pitch;
	int		j;
	
	SDL_FillRect(info_marc, NULL, take_color_player(4, info_marc->format));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
			info_marc->h - 10}, take_color_player(-1, info_marc->format));
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){0, Graph->square_info->h +
		info_marc->h * i, info_marc->w, info_marc->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(info_marc);
	j = -1;
	while (++j < info_marc->h)
		memcpy(pixel + j * pitch, info_marc->pixels + j * info_marc->pitch,
			info_marc->pitch);
	SDL_UnlockSurface(info_marc);
	SDL_UnlockTexture(Graph->info_text);
}

void	ft_ini_information(t_data *data)
{
	SDL_Surface *info_marc;
	t_sdl		*Graph;
	int			i;
	
	Graph = data->arena->Graph;
	Graph->square_info = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	Graph->square_info->w = Graph->screen.w * LEFT_BORDER;
	Graph->square_info->h = Graph->big_square->h / 4;
	Graph->info_text = SDL_CreateTexture(Graph->screen.Renderer, 372645892,
		SDL_TEXTUREACCESS_STREAMING, Graph->square_info->w,
		Graph->big_square->h);
	ini_general(Graph);
	i = 0;
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w,
			(Graph->big_square->h - Graph->square_info->h) / 4, 32, 372645892);
	while(i < MAX_PLAYERS)
		ini_player(Graph, i++, info_marc);
	ft_ini_material(data, Graph);
}
