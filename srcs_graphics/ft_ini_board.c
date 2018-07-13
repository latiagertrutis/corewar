/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/13 14:08:25 by jagarcia         ###   ########.fr       */
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
	if (SDL_FillRects(surf, border, 4, SDL_MapRGB(surf->format, 52, 52, 52)))
		ft_SDL_error("SDL_FillRects", MODE_SDL);
}

static int		initial_pos(int rack_dim, int initial_pos, int longit)
{
	int	ini_ajust;

	ini_ajust = 0;
	while (ini_ajust + longit < rack_dim - ini_ajust)
		ini_ajust++;
	return (ini_ajust + initial_pos);
}

static void		ini_rack(t_sdl *Graph)
{
	int rack_dim[2];
	int square_dim[2];
	int	ajust[2];
	SDL_Rect square;
	int j = 0;

	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
//	SDL_RenderClear(Graph->screen.Renderer);
	rack_dim[0] = Graph->screen.w - (Graph->screen.w * LEFT_BORDER) -
		(Graph->screen.w * RIGHT_BORDER);
	rack_dim[1] = Graph->screen.h - (Graph->screen.h * UPPER_BORDER) -
		(Graph->screen.h * BOTTOM_BORDER);
	if (MEM_SIZE >= 64)
	{
		square_dim[0] = rack_dim[0] / 64;
		square_dim[1] = rack_dim[1] / (MEM_SIZE / 64 + (MEM_SIZE % 64 ? 1 : 0));
//		square_dim[1] = rack_dim[1] / 64;
	}
	else
	{
		square_dim[0] = rack_dim[0];
		square_dim[1] = rack_dim[1] / (MEM_SIZE % 64);
	}
	
	SDL_SetRenderDrawColor(Graph->screen.Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Graph->screen.Renderer, &(SDL_Rect){Graph->screen.w * RIGHT_BORDER,Graph->screen.h * UPPER_BORDER, rack_dim[0], rack_dim[1]});
	SDL_SetRenderDrawColor(Graph->screen.Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	
	ajust[0] = initial_pos(rack_dim[0], Graph->screen.w * RIGHT_BORDER, square_dim[0] * 64);
	ajust[1] = initial_pos(rack_dim[1], Graph->screen.h * UPPER_BORDER, square_dim[1] * 64);
	square = (SDL_Rect){ajust[0], ajust[1], square_dim[0] + 1, square_dim[1] + 1};
	ft_printf("rack_dim = %i x %i\nsquare_dim = %i x %i\n", rack_dim[0], rack_dim[1], square_dim[0], square_dim[1]);
	while (square.x  < rack_dim[0] + square.w)
	{
		square.y = ajust[1];
		while (square.y < rack_dim[1] + square.h)
		{
			if (SDL_RenderDrawRect(Graph->screen.Renderer, &square))
				ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
			square.y += square.h - 1;
		}
		square.x += square.w - 1;
	}
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
	ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);

}

void			ft_ini_board(t_sdl *Graph)
{
	SDL_Surface *surf;
	SDL_Rect border[4];
	SDL_Texture *tex_border;

	if (!(surf = SDL_GetWindowSurface(Graph->screen.window)))
		ft_SDL_error("SDL_GetWindowSurface", MODE_SDL);
	ini_borders(border, Graph, surf);
	if (!(tex_border = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf)))
		ft_SDL_error("SDL_CreateTextureFrommSurface", MODE_SDL);
	if (SDL_RenderCopy(Graph->screen.Renderer, tex_border, NULL, NULL))
		ft_SDL_error("SDL_RenderCopy", MODE_SDL);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex_border);
	ini_rack(Graph);
	SDL_RenderPresent(Graph->screen.Renderer);
}
