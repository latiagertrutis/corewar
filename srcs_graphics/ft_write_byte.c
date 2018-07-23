/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 18:48:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/21 22:36:03 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			take_hexa_byte(unsigned char byte, char hexa[3])
{
	char			*hexa_characters;

	 hexa_characters = "0123456789ABCDEF";
	 hexa[0] = hexa_characters[byte / 16];
	 hexa[1] = hexa_characters[byte % 16];
	 hexa[2] = 0;
}

static SDL_Color	take_color_byte(int id)
{
	if (id == 1)
		return ((SDL_Color){51, 255, 51, SDL_ALPHA_OPAQUE});
	else if (id == 2)
		return ((SDL_Color){255, 204, 0, SDL_ALPHA_OPAQUE});
	else if (id == 3)
		return ((SDL_Color){0xFF, 0xF2, 0xCF, SDL_ALPHA_OPAQUE});
	else if (id == 4)
		return ((SDL_Color){252, 102, 92, SDL_ALPHA_OPAQUE});
	else
		return ((SDL_Color){89, 89, 75, SDL_ALPHA_OPAQUE});
}

void		ft_write_byte(int pos, t_arena *arena, char *pixel, int pitch)
{
	char		hexa_byte[3];
	SDL_Surface *surf_byte;
	SDL_Color	color;
	t_sdl		*Graph;

	Graph = arena->Graph;
	color = take_color_byte(arena->board[pos].id);
	take_hexa_byte(arena->board[pos].mem, hexa_byte);
	SDL_FillRect(Graph->rack_square, NULL, SDL_MapRGBA(Graph->rack_square->format, 0x3D, 0x3D, 0x33, 0xFF));
	if (!(surf_byte = TTF_RenderUTF8_Blended(Graph->font_info.font, hexa_byte, color)))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	Graph->square->x = /* (Graph->screen.w * RIGHT_BORDER) */ + (Graph->square->w - 1) * (pos % Graph->cuant_squares[0]) + 1 /* +(Graph->square->w - surf_byte->w) / 2 */;
	Graph->square->y = /* (Graph->screen.h * UPPER_BORDER) */ + (Graph->square->h - 1) * (pos / Graph->cuant_squares[1]) + 1 /* + (Graph->square->h - surf_byte->h) / 2 */;
//	SDL_ConvertSurfaceFormat(surf_byte, 372645892, 0);
	SDL_BlitSurface(surf_byte, NULL, Graph->rack_square, &(SDL_Rect){(Graph->rack_square->w - surf_byte->w) / 2, (Graph->rack_square->h - surf_byte->h) / 2, surf_byte->w, surf_byte->h});
	SDL_LockSurface(Graph->rack_square);
	for(int j = 0; j < Graph->rack_square->h; j++)
		memcpy(pixel + Graph->square->x * 4 + Graph->square->y * pitch + j * pitch, Graph->rack_square->pixels + j * Graph->rack_square->pitch, Graph->rack_square->pitch);
	SDL_UnlockSurface(Graph->rack_square);
//	if (SDL_BlitSurface(surf_byte, NULL, Graph->screen.screen, &(SDL_Rect){Graph->square->x, Graph->square->y, Graph->square->w - 4, Graph->square->h - 4}))
//		ft_SDL_error("SDL_BlitSurface", MODE_SDL);
	SDL_FreeSurface(surf_byte);
}
