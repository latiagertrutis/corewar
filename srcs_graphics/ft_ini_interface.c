/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/19 17:56:06 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_rack(int cuant_squares[2], t_sdl *Graph, int first_col)
{
	int i;
	int j;
	int	k;

	if (!(Graph->rack = SDL_CreateRGBSurface(0, Graph->screen.w - (Graph->screen.w * RIGHT_BORDER) - (Graph->screen.w * LEFT_BORDER), Graph->screen.h - (Graph->screen.h * UPPER_BORDER) - Graph->screen.h * BOTTOM_BORDER, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK)))
		ft_SDL_error("SDL_CreateRGBSurface", MODE_SDL);
	SDL_FillRect(Graph->rack, NULL, 0xFF0000FF/* 0x3D3D33FF */);
	k = cuant_squares[1];
	i = cuant_squares[0];
	j = -1;
		if (SDL_SetRenderDrawColor(Graph->screen.Renderer, BACK_COLOR
			SDL_ALPHA_OPAQUE))
	ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	while (++j <= MEM_SIZE)
	{
		if (k && !i)
		{
			Graph->square->y += Graph->square->h - 1;
			Graph->square->x = first_col;
			i = cuant_squares[0];
			k--;
		}
//		if (SDL_RenderDrawRect(Graph->screen.Renderer, Graph->square))
		if (SDL_FillRect(Graph->rack, Graph->square, 0x1C1C15FF))
			ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
		if (SDL_FillRect(Graph->rack, &(SDL_Rect){Graph->square->x + 1, Graph->square->y + 1, Graph->square->w - 2, Graph->square->h - 2}, 0x3D3D33FF))
			ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
		Graph->square->x += Graph->square->w - 1;
		i--;
	}
}

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
	draw_rack(Graph->cuant_squares, Graph, Graph->screen.w * RIGHT_BORDER);
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
	draw_rack((int[2]){64, 64}, Graph, 0);
}

void				ft_ini_interface(t_sdl *Graph)
{
	if (!(Graph->screen.screen = SDL_CreateRGBSurface(0, Graph->screen.w, Graph->screen.h, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK)))
		ft_SDL_error("SDL_CreateRGBSurface", MODE_SDL);
	SDL_SetColorKey(Graph->screen.screen, SDL_FALSE, 0x3D3D33FF);
	if (MEM_SIZE <= 4096)
		ini_rack(Graph);
	else
		ini_big_rack(Graph);
	Graph->rack_square = SDL_CreateRGBSurface(0, Graph->square->w - 2,
			Graph->square->h - 2, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);
}
