/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/10 15:20:08 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ini_big_rack(t_sdl *Graph)
{
	int square_dim[2];

	Graph->cuant_squares[0] = 64;
	Graph->cuant_squares[1] = (MEM_SIZE / 64 + (MEM_SIZE % 64 ? 1 : 0));
	square_dim[0] = 0;
	square_dim[1] = 0;
	while (square_dim[0] * Graph->cuant_squares[0] <= Graph->screen.w -
			(Graph->screen.w * LEFT_BORDER) - (Graph->screen.w * RIGHT_BORDER))
		square_dim[0]++;
	while (square_dim[1] * Graph->cuant_squares[1] <= Graph->screen.h -
			(Graph->screen.h * UPPER_BORDER) - (Graph->screen.h * BOTTOM_BORDER))
		square_dim[1]++;
	Graph->square = &(SDL_Rect){Graph->screen.w * RIGHT_BORDER + 1,
			Graph->screen.h * UPPER_BORDER + 1, square_dim[0],
			square_dim[1]};
}

static void				ini_rack(t_sdl *Graph)
{
	int			square_dim[2];

	
	square_dim[0] = 0;
	square_dim[1] = 0;
	Graph->cuant_squares[0] = 64;
	Graph->cuant_squares[1] = 64;
	while (square_dim[0] * 64 <= Graph->screen.w - (Graph->screen.w *
			LEFT_BORDER) - (Graph->screen.w * RIGHT_BORDER))
		square_dim[0]++;
	while (square_dim[1] * 64 <= Graph->screen.h - (Graph->screen.h *
			UPPER_BORDER) - (Graph->screen.h * BOTTOM_BORDER))
		square_dim[1]++;
	if (!(Graph->square = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
				ft_error("Error malloc ini_rack\n");
	Graph->square->x = 0;
	Graph->square->y = 0;
	Graph->square->w = square_dim[0];
	Graph->square->h = square_dim[1];
}

void				ft_ini_interface(t_sdl *Graph, t_data *data)
{
	if (!(Graph->big_square = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("Error malloc ft_ini_interface\n");
	Graph->big_square->x = Graph->screen.w * RIGHT_BORDER;
	Graph->big_square->y = Graph->screen.h * UPPER_BORDER;
	Graph->big_square->w = Graph->screen.w * (1 - RIGHT_BORDER - LEFT_BORDER);
	Graph->big_square->h = Graph->screen.h * (1 - UPPER_BORDER - BOTTOM_BORDER);
	if (!(Graph->rack = SDL_CreateRGBSurfaceWithFormat(0, Graph->big_square->w,
			Graph->big_square->h, 32, 372645892)))
		ft_SDL_error("SDL_CreateRGBSurface", MODE_SDL);
	if (MEM_SIZE <= 4096)
		ini_rack(Graph);
	else
		ini_big_rack(Graph);
	if (!(Graph->screen.texture = SDL_CreateTexture(Graph->screen.Renderer,
			372645892, SDL_TEXTUREACCESS_STREAMING, Graph->big_square->w,
			Graph->big_square->h)))
		ft_SDL_error("SDL_CreateTexture", MODE_SDL);
	if (!(Graph->pc = (SDL_Texture **)malloc(sizeof(SDL_Texture *) *
			MAX_PLAYERS * 4)))
		ft_error("Error malloc ft_ini_interface\n");
	ft_ini_pcs(Graph);
	if (!data->mods->dump)
	{
		SDL_SetTextureBlendMode(Graph->screen.texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(Graph->screen.texture, 100);
	}
}
