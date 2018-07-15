/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/15 16:16:47 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char		*take_hexa_byte(unsigned char byte)
{
	char 			*hexa;
	char			*hexa_characters;

	if (!(hexa = (char *)malloc(sizeof(char) * 3)))
		ft_error("Error malloc take_hexa_byte\n");
	hexa_characters = "0123456789abcdef";
	hexa[0] = hexa_characters[byte / 16];
	hexa[1] = hexa_characters[byte % 16];
	hexa[2] = 0;
	return (hexa);
}

static SDL_Color	take_color(int id)
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

static void		write_byte(int pos[2], t_board board[MEM_SIZE],
		SDL_Surface *surf_board, t_sdl *Graph)
{
	char *hexa_byte;
	SDL_Surface *surf_byte;
	SDL_Color	color;
	SDL_Surface *rack_celd;

	rack_celd = SDL_CreateRGBSurface(0, Graph->square->w - 2, Graph->square->h - 2, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);
	SDL_FillRect(rack_celd, NULL, 0x3D3D33FF);
	color = take_color(board[(pos[1] * Graph->cuant_squares[0] + pos[0])].id);
	hexa_byte = take_hexa_byte(board[(pos[1] * Graph->cuant_squares[0]
				+ pos[0])].mem);
	if (!(surf_byte = TTF_RenderUTF8_Blended(Graph->font_info.font, hexa_byte,
			color)))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	SDL_BlitSurface(surf_byte, NULL, rack_celd, &(SDL_Rect){((Graph->square->w - 2) - surf_byte->w) / 2, ((Graph->square->h - 2) - surf_byte->h) / 2, surf_byte->w, surf_byte->h});
	SDL_FreeSurface(surf_byte);
	Graph->square->x = (Graph->screen.w * RIGHT_BORDER) + (Graph->square->w - 1) * (pos[0]) + 1;
	Graph->square->y = (Graph->screen.h * UPPER_BORDER) + (Graph->square->h - 1) * (pos[1]) + 1;
	SDL_BlitSurface(rack_celd, NULL, surf_board, &(SDL_Rect){Graph->square->x,
		Graph->square->y, Graph->square->w, Graph->square->h});
	SDL_FreeSurface(surf_byte);
	free(hexa_byte);
}

void	ft_board_to_screen(t_sdl *Graph, t_board board[MEM_SIZE])
{
	SDL_Surface *surf_board;
	int			i[2];

	surf_board = SDL_GetWindowSurface(Graph->screen.window);
	i[0] = 0;
	i[1] = 0;
	while (i[1] < Graph->cuant_squares[1])
	{
		i[0] = -1;
		while (++i[0] < Graph->cuant_squares[0])
			write_byte(i, board, surf_board, Graph);
		i[1]++;
	}
	SDL_UpdateWindowSurface(Graph->screen.window);

	
}
