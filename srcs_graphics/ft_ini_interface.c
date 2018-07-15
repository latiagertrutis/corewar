/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/15 15:08:00 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ini_borders(SDL_Rect border[4], t_sdl *Graph, SDL_Surface *surf)
{
	border[0] = (SDL_Rect){Graph->screen.w - (Graph->screen.w * LEFT_BORDER),
				0, LEFT_BORDER * Graph->screen.w, Graph->screen.h};
	border[1] = (SDL_Rect){0, 0, Graph->screen.w, Graph->screen.h * UPPER_BORDER};
	border[2] = (SDL_Rect){0, Graph->screen.h - floor((Graph->screen.h *
			BOTTOM_BORDER)), Graph->screen.w, Graph->screen.h * BOTTOM_BORDER};
	border[3] = (SDL_Rect){0, 0, Graph->screen.w * RIGHT_BORDER, Graph->screen.h};
	if (SDL_FillRects(surf, border, 4, SDL_MapRGBA(surf->format, 28, 28, 21, 255)))
		ft_SDL_error("SDL_FillRects", MODE_SDL);
}

static void		draw_rack(int cuant_squares[2], t_sdl *Graph, int first_col)
{
	int i;
	int j;
	int	k;

	if (SDL_SetRenderDrawColor(Graph->screen.Renderer,28, 28, 21,
			SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	Graph->square->x = Graph->screen.w * RIGHT_BORDER;
	Graph->square->y = Graph->screen.h * UPPER_BORDER;
	k = cuant_squares[1];
	i = cuant_squares[0];
	j = -1;
	while (++j < MEM_SIZE)
	{
		if (k && !i)
		{
			Graph->square->y += Graph->square->h - 1;
			Graph->square->x = first_col;
			i = cuant_squares[0];
			k--;
		}
		if (SDL_RenderDrawRect(Graph->screen.Renderer, Graph->square))
			ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
		Graph->square->x += Graph->square->w - 1;
		i--;
	}
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, 0, 0, 0,
		SDL_ALPHA_OPAQUE))
	ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	SDL_RenderPresent(Graph->screen.Renderer);
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
	Graph->square->x = Graph->screen.w * RIGHT_BORDER;
	Graph->square->y = Graph->screen.h * UPPER_BORDER;
	Graph->square->w = square_dim[0];
	Graph->square->h = square_dim[1];
	draw_rack((int[2]){64, 64}, Graph, Graph->screen.w * RIGHT_BORDER);
}

void				ft_ini_interface(t_sdl *Graph)
{
	SDL_Surface *surf;
	SDL_Rect border[4];
	SDL_Texture *tex_border;

	if (!(surf = SDL_GetWindowSurface(Graph->screen.window)))
		ft_SDL_error("SDL_GetWindowSurface", MODE_SDL);
	ini_borders(border, Graph, surf);
	if (!(tex_border = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf)))
		ft_SDL_error("SDL_CreateTextureFromSurface", MODE_SDL);
	if (SDL_RenderCopy(Graph->screen.Renderer, tex_border, NULL, NULL))
		ft_SDL_error("SDL_RenderCopy", MODE_SDL);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex_border);
	if (MEM_SIZE <= 4096)
		ini_rack(Graph);
	else
		ini_big_rack(Graph);
	SDL_RenderPresent(Graph->screen.Renderer);
}
