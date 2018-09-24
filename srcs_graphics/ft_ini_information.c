/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_information.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 03:49:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/24 22:07:05 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		ini_general(void)
{
	SDL_Surface *info_marc;
	int			i;
	char		*pixel;
	int			pitch;
	
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, g_Graph->square_info->w,
		g_Graph->square_info->h, 32, 372645892);
	SDL_FillRect(info_marc, NULL, ft_MapRGBA(info_marc->format, 4, 0));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
				info_marc->h - 10}, ft_MapRGBA(info_marc->format, 5, 0));
	SDL_LockTexture(g_Graph->info_text, g_Graph->square_info,
		(void **)&pixel, &pitch);
	SDL_LockSurface(info_marc);
	i = -1;
	while (++i < info_marc->h)
		memcpy(pixel + i * pitch, info_marc->pixels + i * info_marc->pitch,
			info_marc->pitch);
	SDL_UnlockSurface(info_marc);
	SDL_UnlockTexture(g_Graph->info_text);
	SDL_FreeSurface(info_marc);
}

static void		ini_player(int i, SDL_Surface *info_marc)
{
	char	*pixel;
	int		pitch;
	int		j;
	
	SDL_FillRect(info_marc, NULL, ft_MapRGBA(info_marc->format, 4, 0));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
			info_marc->h - 10}, ft_MapRGBA(info_marc->format, 5, 0));
	SDL_LockTexture(g_Graph->info_text, &(SDL_Rect){0, g_Graph->square_info->h +
		info_marc->h * i, info_marc->w, info_marc->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(info_marc);
	j = -1;
	while (++j < info_marc->h)
		memcpy(pixel + j * pitch, info_marc->pixels + j * info_marc->pitch,
			info_marc->pitch);
	SDL_UnlockSurface(info_marc);
	SDL_UnlockTexture(g_Graph->info_text);
}

void	ft_ini_information(void)
{
	SDL_Surface *info_marc;
	int			i;

	if (!(g_Graph->square_info = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("ft_memalloc ft_ini_information");
	g_Graph->square_info->w = g_Graph->screen.w * LEFT_BORDER - g_Graph->screen.w * RIGHT_BORDER;
	g_Graph->square_info->h = g_Graph->big_square->h / 4;
	g_Graph->info_text = SDL_CreateTexture(g_Graph->screen.Renderer, 372645892,
		SDL_TEXTUREACCESS_STREAMING, g_Graph->square_info->w,
		g_Graph->big_square->h);
//	ini_general(g_Graph);
	i = 0;
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, g_Graph->square_info->w,
			(g_Graph->big_square->h - g_Graph->square_info->h) / 4, 32, 372645892);
//	while(i < MAX_PLAYERS)
//		ini_player(g_Graph, i++, info_marc);
	ft_ini_material(info_marc);
	if (!(g_Graph->info_marc = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect))))
	    ft_error("malloc ft_ini_information 2");
	*g_Graph->info_marc = (SDL_Rect){g_Graph->screen.w * RIGHT_BORDER + g_Graph->big_square->w + 20, g_Graph->square_info->h + 10, info_marc->w, info_marc->h};
//	SDL_FreeSurface(info_marc);
}
