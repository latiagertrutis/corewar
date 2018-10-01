/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/01 19:50:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void					ini_big_rack(void)
{
	int square_dim[2];

	g_graph->cuant_squares[0] = 64;
	g_graph->cuant_squares[1] = (MEM_SIZE / 64 + (MEM_SIZE % 64 ? 1 : 0));
	square_dim[0] = 0;
	square_dim[1] = 0;
	while (square_dim[0] * g_graph->cuant_squares[0] <= g_graph->screen.w -
			(g_graph->screen.w * LEFT_BORDER) -
			(g_graph->screen.w * RIGHT_BORDER))
		square_dim[0]++;
	while (square_dim[1] * g_graph->cuant_squares[1] <= g_graph->screen.h -
			(g_graph->screen.h * UPPER_BORDER) -
			(g_graph->screen.h * BOTTOM_BORDER))
		square_dim[1]++;
	g_graph->square = &(SDL_Rect){g_graph->screen.w * RIGHT_BORDER + 1,
			g_graph->screen.h * UPPER_BORDER + 1, square_dim[0],
			square_dim[1]};
}

static void					ini_rack(void)
{
	int			square_dim[2];

	square_dim[0] = 0;
	square_dim[1] = 0;
	g_graph->cuant_squares[0] = 64;
	g_graph->cuant_squares[1] = 64;
	while (square_dim[0] * 64 <= g_graph->screen.w - (g_graph->screen.w *
			LEFT_BORDER) - (g_graph->screen.w * RIGHT_BORDER))
		square_dim[0]++;
	while (square_dim[1] * 64 <= g_graph->screen.h - (g_graph->screen.h *
			UPPER_BORDER) - (g_graph->screen.h * BOTTOM_BORDER))
		square_dim[1]++;
	if (!(g_graph->square = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("Error malloc ini_rack\n");
	g_graph->square->x = 0;
	g_graph->square->y = 0;
	g_graph->square->w = square_dim[0];
	g_graph->square->h = square_dim[1];
}

/*
**Para dump hay que hacer que el textur blend y el alpha mod no se activen
**cuando se use el modo dump
*/

static void					prepare_big_square(void)
{
	if (!(g_graph->big_square = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("Error malloc ft_ini_interface\n");
	g_graph->big_square->x = g_graph->screen.w * RIGHT_BORDER;
	g_graph->big_square->y = g_graph->screen.h * UPPER_BORDER;
	g_graph->big_square->w = g_graph->screen.w *
			(1 - RIGHT_BORDER - LEFT_BORDER);
	g_graph->big_square->h = g_graph->screen.h *
			(1 - UPPER_BORDER - BOTTOM_BORDER);
}

void						ft_ini_interface(void)
{
	int i;

	i = MAX_PLAYERS;
	prepare_big_square();
	if (!(g_graph->rack = SDL_CreateRGBSurfaceWithFormat(0,
			g_graph->big_square->w, g_graph->big_square->h, 32, 372645892)))
		ft_sdl_error("SDL_CreateRGBSurface", MODE_SDL);
	if (MEM_SIZE <= 4096)
		ini_rack();
	else
		ini_big_rack();
	if (!(g_graph->screen.texture = SDL_CreateTexture(g_graph->screen.Renderer,
			372645892, SDL_TEXTUREACCESS_STREAMING, g_graph->big_square->w,
			g_graph->big_square->h)))
		ft_sdl_error("SDL_CreateTexture", MODE_SDL);
	if (!(g_graph->pc = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * i * 4)))
		ft_error("Error malloc ft_ini_interface\n");
	ft_ini_pcs();
	if (SDL_SetTextureBlendMode(g_graph->screen.texture, SDL_BLENDMODE_BLEND))
		ft_sdl_error("SDL_SetTextureBlendMode", MODE_SDL);
	if (SDL_SetTextureAlphaMod(g_graph->screen.texture, 100))
		ft_sdl_error("SDL_SetTextureAlphaMod", MODE_SDL);
}
