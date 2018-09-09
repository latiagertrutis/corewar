/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/09 19:04:28 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			take_hexa_byte(unsigned char byte, char hexa_byte[3])
{
	char			*hexa_characters;

	hexa_characters = "0123456789ABCDEF";
	hexa_byte[0] = hexa_characters[byte / 16];
	hexa_byte[1] = hexa_characters[byte % 16];
	hexa_byte[2] = 0;
	return (byte);
}

static int			take_color_byte(t_board byte, t_data *data)
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

static void			write_byte(int pos, t_board board[MEM_SIZE], t_sdl *Graph, t_data *data)
{
	char		hexa_byte[3];
	SDL_Surface *surf_byte;
	SDL_Surface *tmp;

	Graph->square->x = (Graph->square->w - 1) * (pos % Graph->cuant_squares[0]);
	Graph->square->y = (Graph->square->h - 1) * (pos / Graph->cuant_squares[1]);
	surf_byte = NULL;
	if (data->mods->info)
		surf_byte = Graph->hexa_bytes[take_color_byte(board[pos], data)]
			[take_hexa_byte(board[pos].mem, hexa_byte)];
	else
	{
		if (board[pos].id - 1 >= 0)
			surf_byte = Graph->hexa_bytes[9][take_color_byte(board[pos], data)];
		else
			surf_byte = Graph->hexa_bytes[9][4];
	}
	if (!(tmp = SDL_ConvertSurfaceFormat(surf_byte, 372645892, 0)))
		ft_SDL_error("SDL_ConvertSurfaceFormat", MODE_SDL);
	SDL_BlitSurface(tmp, NULL, Graph->rack,
		&(SDL_Rect){Graph->square->x + 1, Graph->square->y,
		tmp->w, tmp->h});
	if (!data->mods->pause)
		board[pos].new = board[pos].new ? board[pos].new - 1 : 0;
	SDL_FreeSurface(tmp);
}

void	ft_board_to_screen(t_sdl *Graph, t_board board[MEM_SIZE], t_data *data)
{
	int			i;
	char		*pixel;
	int			pitch;
	SDL_Surface	*rack;
	SDL_Texture	*texture;

	i = 0;
	while (i < MEM_SIZE)
		write_byte(i++, board, Graph, data);
	rack = Graph->rack;
	texture = Graph->screen.texture;
	SDL_LockTexture(Graph->screen.texture, NULL, (void **)&pixel, &pitch);
	SDL_LockSurface(rack);
	i = -1;
	while (++i < rack->h)
		memcpy(pixel + i * pitch, rack->pixels + i * rack->pitch,
			rack->pitch);
	SDL_UnlockSurface(rack);
	SDL_UnlockTexture(Graph->screen.texture);
}
