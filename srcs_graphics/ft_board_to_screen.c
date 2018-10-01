/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/01 19:50:28 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int			take_hexa_byte(unsigned char byte, char hexa_byte[3])
{
	char			*hexa_characters;

	hexa_characters = "0123456789ABCDEF";
	hexa_byte[0] = hexa_characters[byte / 16];
	hexa_byte[1] = hexa_characters[byte % 16];
	hexa_byte[2] = 0;
	return (byte);
}

static int			take_color_byte(t_board byte)
{
	if (!byte.new)
	{
		if (byte.id == 1)
			return (0);
		else if (byte.id == 2)
			return (1);
		else if (byte.id == 3)
			return (2);
		else if (byte.id == 4)
			return (3);
		else
			return (4);
	}
	else
	{
		if (byte.id == 1)
			return (5);
		else if (byte.id == 2)
			return (6);
		else if (byte.id == 3)
			return (7);
		else
			return (8);
	}
}

static void			write_byte(int pos, const t_board *board,
		int cuant_squares[2])
{
	char		hexa_byte[3];
	SDL_Surface *surf_byte;
	SDL_Surface *tmp;

	g_graph->square->x = (g_graph->square->w - 1) * (pos % cuant_squares[0]);
	g_graph->square->y = (g_graph->square->h - 1) * (pos / cuant_squares[1]);
	surf_byte = NULL;
	if (g_hexl)
		surf_byte = g_graph->hexa_bytes[take_color_byte(board[pos])]
			[take_hexa_byte(board[pos].mem, hexa_byte)];
	else
	{
		if (board[pos].id - 1 >= 0)
			surf_byte = g_graph->hexa_bytes[9][take_color_byte(board[pos])];
		else
			surf_byte = g_graph->hexa_bytes[9][4];
	}
	if (!(tmp = SDL_ConvertSurfaceFormat(surf_byte, 372645892, 0)))
		ft_sdl_error("SDL_ConvertSurfaceFormat", MODE_SDL);
	SDL_BlitSurface(tmp, NULL, g_graph->rack,
		&(SDL_Rect){g_graph->square->x + 1, g_graph->square->y,
		tmp->w, tmp->h});
	SDL_FreeSurface(tmp);
}

void				ft_board_to_screen(const t_board *board)
{
	int			i;
	char		*pixel;
	int			pitch;
	SDL_Surface	*rack;
	SDL_Texture	*texture;

	i = 0;
	while (i < MEM_SIZE)
		write_byte(i++, board, g_graph->cuant_squares);
	rack = g_graph->rack;
	texture = g_graph->screen.texture;
	SDL_LockTexture(g_graph->screen.texture, NULL, (void **)&pixel, &pitch);
	SDL_LockSurface(rack);
	i = -1;
	while (++i < rack->h)
		ft_memcpy(pixel + i * pitch, rack->pixels + i * rack->pitch,
			rack->pitch);
	SDL_UnlockSurface(rack);
	SDL_UnlockTexture(g_graph->screen.texture);
}
