/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_data_surfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:02:57 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/29 17:52:55 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Color	take_color(int i)
{
	if (i == 0)
		return ((SDL_Color){51, 255, 51, SDL_ALPHA_OPAQUE});
	else if (i == 1)
		return ((SDL_Color){255, 204, 0, SDL_ALPHA_OPAQUE});
	else if (i == 2)
		return ((SDL_Color){255, 242, 207, SDL_ALPHA_OPAQUE});
	else
		return ((SDL_Color){252, 102, 92, SDL_ALPHA_OPAQUE});
}

static void		put_general_info(t_sdl *Graph)
{
	int			tmp;
	int			x_pos;

	Graph->font[TMP_FONT].font_size = Graph->font[FIELD_FONT].font_size * 2;
	Graph->font[TMP_FONT].font = TTF_OpenFont("./whitrabt.ttf", Graph->font[TMP_FONT].font_size);
	TTF_SizeUTF8(Graph->font[TMP_FONT].font, "A", &Graph->font[TMP_FONT].w, &Graph->font[TMP_FONT].h);
	x_pos = 50;
	Graph->font[TMP_FONT].color = (SDL_Color){255, 255, 255, 255};
	Graph->font[GENERAL_NBR_FONT].color = Graph->font[TMP_FONT].color;
	tmp = 15;
	tmp += ft_write_string(Graph, "Number of Cycles", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp});
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr) + 10;
	tmp += ft_write_string(Graph, "Cycles to Die", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp});
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr) + 10;
	tmp += ft_write_string(Graph, "Number of Processos", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp});
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr);
}

static void		put_player_info(t_sdl *Graph, SDL_Surface *info_marc, t_data *data)
{
	int			tmp;
	int			x_pos;
	unsigned int			i;

	x_pos = 50;
	i = -1;
	while (++i < data->n_players)
	{
		Graph->font[TMP_FONT].color = take_color(i);
		Graph->font[PLAYER_NBR_FONT].color = Graph->font[TMP_FONT].color;
		tmp = Graph->square_info->h + 20 + info_marc->h * i;
		tmp += ft_write_string(Graph, data->players[i].name, (int[2]){x_pos + (Graph->player_nbr->w * 10 - 9) / 2, tmp});
//		tmp += ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr) + 10;
		tmp += ft_write_string(Graph, "Number of Lifes", (int[2]){x_pos + (Graph->player_nbr->w * 10 - 9) / 2, tmp});
		tmp += ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr) + 10;
		tmp += ft_write_string(Graph, "Last Life", (int[2]){x_pos + (Graph->player_nbr->w * 10 - 9) / 2, tmp});
		tmp += ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT], (int[2]){x_pos, tmp}, *Graph->general_nbr) + 10;
	}
}

static void		ini_number(t_sdl *Graph, int mode, Uint32 color, SDL_Surface **number)
{
	*number = SDL_CreateRGBSurfaceWithFormat(0, 40, 60, 32, Graph->rack->format->format);
	SDL_FillRect(*number, NULL, color);
	SDL_FillRect(*number, &(SDL_Rect){2, 2, (*number)->w - 4, (*number)->h - 4}, SDL_MapRGBA((*number)->format, 0, 0, 0, 255));
	while (Graph->font[mode].w + 10 < (*number)->w && Graph->font[mode].h + 10 < (*number)->h)
	{
		if (Graph->font[mode].font)
			TTF_CloseFont(Graph->font[mode].font);
		if (!(Graph->font[mode].font = TTF_OpenFont("./whitrabt.ttf", ++Graph->font[mode].font_size)))
			ft_SDL_error("TTF_OpenFont", MODE_TTF);
		TTF_SizeUTF8(Graph->font[mode].font, "0", &Graph->font[mode].w, &Graph->font[mode].h);
	}
}

void	ft_ini_material(t_data *data, t_sdl *Graph, SDL_Surface *info_marc)
{
//	int i;
//
//	i = 0;
	ini_number(Graph, GENERAL_NBR_FONT, SDL_MapRGBA(Graph->rack->format, 255, 255, 255, 255), &Graph->general_nbr);
	put_general_info(Graph);
	ini_number(Graph, PLAYER_NBR_FONT, SDL_MapRGBA(Graph->rack->format, 51, 255, 51, 255), &Graph->player_nbr);
	put_player_info(Graph, info_marc, data);
}
