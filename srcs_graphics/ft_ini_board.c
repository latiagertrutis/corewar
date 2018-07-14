/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 11:09:42 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/14 14:55:13 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_write_byte(int pos[2], char byte, SDL_Surface *surf_board, t_sdl *Graph)
{
	char *hexa_byte;
	char *tmp;
	SDL_Surface *surf_byte;

	hexa_byte = ft_ltoa_base(byte, 16);
	if (strlen(hexa_byte) == 1)
	{
		tmp = ft_strdup("00\0");
		tmp[1] = *hexa_byte;
		free(hexa_byte);
		hexa_byte = tmp;
	}
	if (!(surf_byte = TTF_RenderUTF8_Blended(Graph->font, hexa_byte, (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE})))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	Graph->square->x = (Graph->square->w - 1) * (pos[0]) + 1;
	Graph->square->y = (Graph->square->h - 1) * (pos[1]) + 1;
	ft_printf("pos = %i x %i\n", pos[0], pos[1]);
	ft_printf("square mide %i x %i\n", Graph->square->w, Graph->square->h);
	SDL_BlitSurface(surf_byte, NULL, surf_board, &(SDL_Rect){Graph->square->x, Graph->square->y, Graph->square->w, Graph->square->h});
	SDL_FreeSurface(surf_byte);
}

void		ft_ini_board(t_sdl *Graph, t_board board[MEM_SIZE])
{
	int	font_dim[2];
	int	font_size;
	int	i[2];
	SDL_Surface *surf_board;
	SDL_Texture *text_board;

	if (!(surf_board = SDL_CreateRGBSurface(0, Graph->screen.w -
			(Graph->screen.w * RIGHT_BORDER) - (Graph->screen.w * LEFT_BORDER),
			Graph->screen.h - (Graph->screen.h * UPPER_BORDER) -
			(Graph->screen.h * BOTTOM_BORDER), 32, 0xFF000000, 0x00FF0000,
			0x0000FF00, 0x000000FF)))
		ft_SDL_error("SDL_CreateRGBSurface", MODE_SDL);
	font_size = 1;
	font_dim[0] = 0;
	font_dim[1] = 0;
	ft_printf("square mide %i x %i\n", Graph->square->w, Graph->square->h);
	while (font_dim[0] < Graph->square->w && font_dim[1] < Graph->square->h)
	{
		if (Graph->font)
			TTF_CloseFont(Graph->font);
		if (!(Graph->font = TTF_OpenFont("./Ubuntu-B.ttf", font_size++)))
			ft_SDL_error("TTF_OpenFont", MODE_TTF);
		TTF_SizeUTF8(Graph->font, "FF", font_dim, font_dim + 1);
	}
	i[0] = 0;
	i[1] = 0;
	while (i[1] < Graph->cuant_squares[1])
	{
		i[0] = 0;
		while (i[0] < Graph->cuant_squares[0])
		{
			ft_write_byte(i, board[(i[1] * Graph->cuant_squares[0] + i[0])].mem, surf_board, Graph);
			i[0]++;
		}
		i[1]++;
	}
	text_board = SDL_CreateTextureFromSurface(Graph->screen.Renderer, surf_board);
	SDL_FreeSurface(surf_board);
	SDL_RenderCopy(Graph->screen.Renderer, text_board, NULL, &(SDL_Rect){Graph->screen.w * RIGHT_BORDER, Graph->screen.h * UPPER_BORDER, surf_board->w, surf_board->h});
	SDL_RenderPresent(Graph->screen.Renderer);
}
