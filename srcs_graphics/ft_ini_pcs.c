/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_pcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:57:43 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/16 16:11:44 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			paint_pc(int *pixel, int pitch, SDL_Rect pc, Uint32 color)
{
	int		i;
	int		j;

	i = 0;
	while (i < pc.h)
	{
		j = 0;
		while (j < pc.w)
			pixel[i * pitch / 4 + j++] = color;
		i++;
	}
}

void			ft_ini_pcs(t_sdl *Graph)
{
	int			i;
	SDL_Rect	pc;
	int			*pixel;
	int			pitch;
	Uint32		color;

	pc = (SDL_Rect){0, 0, Graph->square->w - 2, Graph->square->h - 2};
	i = -1;
	while (++i < MAX_PLAYERS * 4)
	{
		color = ft_MapRGBA(Graph->rack->format, i, 1);
		if (!(Graph->pc[i] = SDL_CreateTexture(Graph->screen.Renderer,
				372645892, SDL_TEXTUREACCESS_STREAMING, Graph->square->w - 2,
				Graph->square->h - 2)))
			ft_SDL_error("SDL_CreateTexture", MODE_SDL);
		SDL_SetTextureBlendMode(Graph->pc[i], SDL_BLENDMODE_BLEND);
		SDL_LockTexture(Graph->pc[i], &pc, (void **)&pixel, &pitch);
		paint_pc(pixel, pitch, pc, color);
		SDL_UnlockTexture(Graph->pc[i]);
	}
}
