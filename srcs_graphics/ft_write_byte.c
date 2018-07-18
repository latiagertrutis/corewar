/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 18:48:02 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/17 09:17:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char		*take_hexa_byte(unsigned char byte)
{
	char 			*hexa;
	char			*hexa_characters;

	if (!(hexa = (char *)malloc(sizeof(char) * 64 * 5 + 1)))
		ft_error("Error malloc take_hexa_byte\n");
	 hexa_characters = "0123456789ABCDEF";
	 hexa[0] = hexa_characters[byte / 16];
	 hexa[1] = hexa_characters[byte % 16];
	 hexa[3] = 0;
	return (hexa);
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

 void		ft_write_byte(int pos, t_board byte, t_sdl *Graph)
{
	char *hexa_byte;
	SDL_Surface *surf_byte;
	SDL_Color	color;
	
	SDL_FillRect(Graph->rack_square, NULL, 0x3D3D33FF);
	color = take_color_byte(byte.id);
	hexa_byte = take_hexa_byte(byte.mem);
	if (!(surf_byte = TTF_RenderUTF8_Blended(Graph->font_info.font, hexa_byte,
			color)))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	SDL_BlitSurface(surf_byte, NULL, Graph->rack_square, &(SDL_Rect){((Graph->square->w - 2) - surf_byte->w) / 2, ((Graph->square->h - 2) - surf_byte->h) / 2, surf_byte->w, surf_byte->h});
	SDL_FreeSurface(surf_byte);
	Graph->square->x = (Graph->screen.w * RIGHT_BORDER) + (Graph->square->w - 1) * (pos % Graph->cuant_squares[0]) + 1;
	Graph->square->y = (Graph->screen.h * UPPER_BORDER) + (Graph->square->h - 1) * (pos / Graph->cuant_squares[1]) + 1;
	SDL_BlitSurface(Graph->rack_square, NULL, Graph->screen.screen, &(SDL_Rect){Graph->square->x,
		Graph->square->y, Graph->square->w * 64, Graph->square->h});
	free(hexa_byte);
}
