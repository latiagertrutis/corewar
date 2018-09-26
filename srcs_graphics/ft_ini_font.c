/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 11:09:42 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/15 21:41:46 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		insert_hexa_surf(char pair[3], t_sdl *Graph, int index[3])
{
	SDL_Surface *rack_square;
	SDL_Surface *tmp;
	
	rack_square = SDL_CreateRGBSurfaceWithFormat(0, Graph->square->w,
		Graph->square->h, 32, Graph->rack->format->format);
	SDL_FillRect(rack_square, NULL, ft_MapRGBA(rack_square->format, 4, 0));
	SDL_FillRect(rack_square, &(SDL_Rect){1, 1, rack_square->w - 2,
		rack_square->h - 2}, ft_MapRGBA(rack_square->format, 5, 0));
	tmp = TTF_RenderUTF8_Blended(Graph->font[0].font, pair,
		ft_SDL_color(index[2]));
	SDL_BlitSurface(tmp, NULL, rack_square,
		&(SDL_Rect){(rack_square->w - tmp->w) / 2,
		(rack_square->h - tmp->h) / 2,
		tmp->w, tmp->h});
	Graph->hexa_bytes[index[2]][index[0] * 16 + index[1]] = rack_square;
	SDL_FreeSurface(tmp);
}

static void		generate_noinfo_squares(t_sdl *Graph)
{
	SDL_Surface *rack_square;
	int			i;
	SDL_Color	c;

	i = 0;
	while (i < 9)
	{
		c = ft_SDL_color(i);
		rack_square = SDL_CreateRGBSurfaceWithFormat(0, Graph->square->w,
			Graph->square->h, 32, Graph->rack->format->format);
		SDL_FillRect(rack_square, NULL, ft_MapRGBA(rack_square->format, 4, 0));
		SDL_FillRect(rack_square, &(SDL_Rect){1, 1, rack_square->w - 2,
			rack_square->h - 2}, SDL_MapRGBA(rack_square->format,
			c.r, c.g, c.b, c.a));
		Graph->hexa_bytes[9][i++] = rack_square;
	}
}

static void		generate_hexadecimals(t_sdl *Graph)
{
	int i;
	int j;
	int k;
	char hexa_characters[3];

	hexa_characters[2] = 0;
	k = 0;
	Graph->hexa_bytes = (SDL_Surface ***)malloc(sizeof(SDL_Surface **) * 10);
	while (k < 9)
	{
		i = 0;
		Graph->hexa_bytes[k] = (SDL_Surface **)malloc(sizeof(SDL_Surface *)
			* 16 * 16);
		while (i < 16)
		{
			hexa_characters[0] = (i >= 10 ? 'A' + i - 10 : '0' + i);
			j = -1;
			while (++j < 16)
			{
				hexa_characters[1] = (j >= 10 ? 'A' + j - 10 : '0' + j);
				insert_hexa_surf(hexa_characters, Graph, (int[3]){i, j, k});
			}
			i++;
		}
		k++;
	}
	Graph->hexa_bytes[9] = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * 9);
	generate_noinfo_squares(Graph);
}

void		ft_ini_font(t_sdl *Graph)
{
	int	font_size;

	font_size = 1;
	ft_printf("square mide %i x %i\n", Graph->square->w, Graph->square->h);
	while (Graph->font[0].w + 5 < Graph->square->w && Graph->font[0].h + 5
			< Graph->square->h)
	{
		if (Graph->font[0].font)
			TTF_CloseFont(Graph->font[0].font);
		if (!(Graph->font[0].font =
				TTF_OpenFont("./whitrabt.ttf", font_size++)))
			ft_SDL_error("TTF_OpenFont", MODE_TTF);
		TTF_SizeUTF8(Graph->font[0].font, "FF", &Graph->font[0].w,
				&Graph->font[0].h);
	}
	Graph->font[0].font_size = font_size;
	generate_hexadecimals(Graph);
	
}
