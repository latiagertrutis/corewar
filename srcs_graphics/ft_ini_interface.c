/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/25 19:51:22 by jagarcia         ###   ########.fr       */
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

static Uint32	take_color_pc(int id, SDL_PixelFormat *format)
{
	int mod;

	mod = 5;
	if (!id)
		return (SDL_MapRGBA(format, 51, 255, 51, 128));
	else if (id == 1)
		return (SDL_MapRGBA(format, 255, 204, 0, 128));
	else if (id == 2)
		return (SDL_MapRGBA(format, 0xFF, 0xF2, 0xCF, 128));
	else if (id == 3)
		return (SDL_MapRGBA(format, 252, 102, 92, 128));
	else if (id == 4)
		return (SDL_MapRGBA(format, 51, 255, 51, 178));
	else if (id == 5)
		return (SDL_MapRGBA(format, 255, 204, 0, 178));
	else if (id == 6)
		return (SDL_MapRGBA(format, 0xFF, 0xF2, 0xCF, 178));
	else
		return (SDL_MapRGBA(format, 252, 102, 92, 178));
		
}

static void			ini_pcs(t_sdl *Graph)
{
	int			i[3];
	SDL_Rect	pc;
	int			*pixel;
	int			pitch;
	Uint32		color;

	pc = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	i[0] = 0;
	while (i[0] < MAX_PLAYERS * 2)
	{
		color = take_color_pc(i[0], Graph->rack->format);
		if (!(Graph->pc[i[0]] = SDL_CreateTexture(Graph->screen.Renderer,
				372645892, SDL_TEXTUREACCESS_STREAMING, Graph->square->w - 2,
				Graph->square->h - 2)))
			ft_SDL_error("SDL_CreateTexture", MODE_SDL);
		SDL_SetTextureBlendMode(Graph->pc[i[0]], SDL_BLENDMODE_BLEND);
		SDL_LockTexture(Graph->pc[i[0]], &pc, (void **)&pixel, &pitch);
		i[1] = 0;
		while (i[1] < pc.h)
		{
			i[2] = 0;
			while (i[2] < pc.w)
				pixel[i[1] * pitch / 4 + i[2]++] = color;
			i[1]++;
		}
		SDL_UnlockTexture(Graph->pc[i[0]]);
		i[0]++;
	}
}

void				ft_ini_interface(t_sdl *Graph)
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
			MAX_PLAYERS * 2)))
		ft_error("Error malloc ft_ini_interface\n");
	ini_pcs(Graph);
	SDL_SetTextureBlendMode(Graph->screen.texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(Graph->screen.texture, 100);
}
