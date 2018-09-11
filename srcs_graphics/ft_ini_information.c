/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_information.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 03:49:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/11 18:59:36 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ini_general(t_sdl *Graph)
{
	SDL_Surface *info_marc;
	int			i;
	char		*pixel;
	int			pitch;
	
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w,
		Graph->square_info->h, 32, 372645892);
	SDL_FillRect(info_marc, NULL, ft_MapRGBA(info_marc->format, 4, 0));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
				info_marc->h - 10}, ft_MapRGBA(info_marc->format, 5, 0));
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
	
	SDL_FillRect(info_marc, NULL, ft_MapRGBA(info_marc->format, 4, 0));
	SDL_FillRect(info_marc, &(SDL_Rect){5, 5, info_marc->w - 10,
			info_marc->h - 10}, ft_MapRGBA(info_marc->format, 5, 0));
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
	SDL_Rect 	*tmp;
	
	Graph = data->arena->Graph;
	if (!(tmp = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("ft_memalloc ft_ini_information");
	Graph->square_info = tmp;
	Graph->square_info->w = Graph->screen.w * LEFT_BORDER - Graph->screen.w * RIGHT_BORDER;
	Graph->square_info->h = Graph->big_square->h / 4;
	Graph->info_text = SDL_CreateTexture(Graph->screen.Renderer, 372645892,
		SDL_TEXTUREACCESS_STREAMING, Graph->square_info->w,
		Graph->big_square->h);
//	ini_general(Graph);
	i = 0;
	ft_putchar('Y');
	info_marc = SDL_CreateRGBSurfaceWithFormat(0, Graph->square_info->w,
			(Graph->big_square->h - Graph->square_info->h) / 4, 32, 372645892);
//	while(i < MAX_PLAYERS)
//		ini_player(Graph, i++, info_marc);
	ft_printf("Voy a iniciar el material\n");
	ft_ini_material(data, Graph, info_marc);
	SDL_FreeSurface(info_marc);
}
