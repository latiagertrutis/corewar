/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 06:40:13 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/13 07:13:30 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ini_borders(SDL_Rect border[4], t_sdl *Game)
{
	border[0] = (SDL_Rect){Game->screen.w - (Game->screen.w * LEFT_BORDER),
				0, LEFT_BORDER * Game->screen.w, Game->screen.h};
	border[1] = (SDL_Rect){0, 0, Game->screen.w, Game->screen.h * UPPER_BORDER};
	border[2] = (SDL_Rect){0, Game->screen.h - floor((Game->screen.h *
			BOTTOM_BORDER)), Game->screen.w, Game->screen.h * BOTTOM_BORDER};
	border[3] = (SDL_Rect){0, 0, Game->screen.w * RIGHT_BORDER, Game->screen.h};
}

static SDL_Rect	ini_rack(t_sdl *Game)
{
	int rack_dim[2];
	int square_dim[2];

	rack_dim[0] = Game->screen.w - (Game->screen.w * LEFT_BORDER) -
		(Game->screen.w * RIGHT_BORDER);
	rack_dim[1] = Game->screen.h - (Game->screen.h * UPPER_BORDER) -
		(Game->screen.h * RIGHT_BORDER);
	if (MEM_SIZE > 64)
		square_dim[0] = rack_dim[0] / 64;
	else
		square_dim[0] = rack_dim[0] / MEM_SIZE;
	square_dim[1] = rack_dim[1] / ((MEM_SIZE / 64) + 1);
}

void			ft_ini_board(t_sdl *Game)
{
	SDL_Surface *surf;
	SDL_Rect border[4];
	SDL_Rect rack;
	SDL_Texture *tex_border;

	if (!(surf = SDL_GetWindowSurface(Game->screen.window)))
		ft_SDL_error("SDL_GetWindowSurface", MODE_SDL);
	ini_borders(border, Game);
	rack = ini_rack(Game);
	if (!(SDL_FillRects(surf, border, 4, SDL_MapRGB(surf->format, 52, 52, 52))))
		ft_SDL_error("SDL_FillRects", MODE_SDL);
	if (!(tex_border = SDL_CreateTextureFromSurface(Game->screen.Renderer, surf)))
		ft_SDL_error("SDL_CreateTextureFrommSurface", MODE_SDL);
	if (!(SDL_RenderCopy(Game->screen.Renderer, tex_border, NULL, NULL)))
		ft_SDL_error("SDL_RenderCopy", MODE_SDL);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex_border);
}
