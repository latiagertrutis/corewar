/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_information.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 03:49:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/01 19:50:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	ft_ini_information(void)
{
	SDL_Surface *info_marc;

	if (!(g_graph->square_info = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("ft_memalloc ft_ini_information");
	g_graph->square_info->w = g_graph->screen.w * LEFT_BORDER -
		g_graph->screen.w * RIGHT_BORDER;
	g_graph->square_info->h = g_graph->big_square->h / 4;
	if (!(g_graph->info_text = SDL_CreateTexture(g_graph->screen.Renderer,
		372645892, SDL_TEXTUREACCESS_STREAMING, g_graph->square_info->w,
		g_graph->big_square->h)))
		ft_sdl_error("SDL_CreateTexture", MODE_SDL);
	if (!(info_marc = SDL_CreateRGBSurfaceWithFormat(0, g_graph->square_info->w,
		(g_graph->big_square->h - g_graph->square_info->h) / 4, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	ft_ini_material(info_marc);
	if (!(g_graph->info_marc = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect))))
		ft_error("malloc ft_ini_information 2");
	*g_graph->info_marc = (SDL_Rect){g_graph->screen.w * RIGHT_BORDER +
		g_graph->big_square->w + 20, g_graph->square_info->h + 10,
		info_marc->w, info_marc->h};
}
