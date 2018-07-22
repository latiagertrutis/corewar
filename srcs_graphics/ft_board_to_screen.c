/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/22 15:23:42 by jagarcia         ###   ########.fr       */
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

static void			text_to_texture(t_sdl *Graph, char *pixel, int pitch)
{
	int	i;

	i = 0;
	SDL_LockSurface(Graph->rack_square);
//	for(int j = 0; j < surf_byte->h; j++)
//		memcpy(pixel + (Graph->square->x + 1) * pitch / Graph->big_square->w + (Graph->square->y + 1) * pitch + j * pitch, surf_byte->pixels + j * surf_byte->pitch, surf_byte->pitch);
	while (i < Graph->rack_square->h)
	{
		ft_memcpy(pixel + (Graph->square->x + 1) * pitch / Graph->big_square->w +
			(Graph->square->y + 1) * pitch + i * pitch,
			Graph->rack_square->pixels + i * Graph->rack_square->pitch,
			Graph->rack_square->pitch);
		i++;
	}
	SDL_UnlockSurface(Graph->rack_square);
}

static void			write_byte(int pos, t_arena *arena, char *pixel, int pitch)
{
	char		hexa_byte[3];
	SDL_Surface *surf_byte;
	SDL_Color	color;
	t_sdl		*Graph;
	SDL_Surface *tmp;

	Graph = arena->Graph;
	color = take_color_byte(arena->board[pos].id);
	take_hexa_byte(arena->board[pos].mem, hexa_byte);
	SDL_FillRect(Graph->rack_square, NULL,
		SDL_MapRGBA(Graph->rack_square->format, 0x3D, 0x3D, 0x33, 0xFF));
	if (!(surf_byte = TTF_RenderUTF8_Blended(Graph->font_info.font, hexa_byte,
		color)))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	Graph->square->x = (Graph->square->w - 1) * (pos % Graph->cuant_squares[0]);
	Graph->square->y = (Graph->square->h - 1) * (pos / Graph->cuant_squares[1]);
	tmp = SDL_ConvertSurfaceFormat(surf_byte, 372645892, 0);
	SDL_FreeSurface(surf_byte);
	SDL_BlitSurface(tmp, NULL, Graph->rack_square,
		&(SDL_Rect){(Graph->rack_square->w - tmp->w) / 2,
		(Graph->rack_square->h - tmp->h) / 2,
		tmp->w, tmp->h});
	SDL_FreeSurface(tmp);
	text_to_texture(Graph, pixel, pitch);
}

void	ft_board_to_screen(t_sdl *Graph, t_arena *arena)
{
	int			i;
	char		*pixel;
	int			pitch;

	i = 0;
	SDL_LockTexture(Graph->screen.texture, NULL, (void **)&pixel, &pitch);
//	usleep(10000);
	while (i < MEM_SIZE)
		write_byte(i++, arena, pixel, pitch);
	SDL_UnlockTexture(Graph->screen.texture);
}
