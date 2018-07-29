/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_data_surfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:02:57 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/29 21:43:58 by jagarcia         ###   ########.fr       */
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
	SDL_Surface *tmp_surf;

	Graph->font[TMP_FONT].font_size = Graph->font[FIELD_FONT].font_size * 2;
	Graph->font[TMP_FONT].font = TTF_OpenFont("./whitrabt.ttf", Graph->font[TMP_FONT].font_size);
	TTF_SizeUTF8(Graph->font[TMP_FONT].font, "A", &Graph->font[TMP_FONT].w, &Graph->font[TMP_FONT].h);
	x_pos = 50;
	Graph->font[TMP_FONT].color = (SDL_Color){255, 255, 255, 255};
	Graph->font[GENERAL_NBR_FONT].color = Graph->font[TMP_FONT].color;
	tmp = 15;
	tmp_surf = ft_write_string(Graph, "Number of Cycles", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp}, 1);
	tmp += tmp_surf->h;
	SDL_FreeSurface(tmp_surf);
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, Graph->general_nbr) + 10;
	//aqui hay que rellenar el Rect de  number of cycles
	tmp_surf = ft_write_string(Graph, "Cycles to Die", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp}, 1);
	tmp += tmp_surf->h;
	SDL_FreeSurface(tmp_surf);
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, Graph->general_nbr) + 10;
	//aqui hay que rellenar el Rect de  cycles to die
	tmp_surf = ft_write_string(Graph, "Number of Processos", (int[2]){x_pos + (Graph->general_nbr->w * 10 - 9) / 2, tmp}, 1);
	tmp += tmp_surf->h;
	SDL_FreeSurface(tmp_surf);
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT], (int[2]){x_pos, tmp}, Graph->general_nbr);
	//aqui hay que rellenar el Rect de  processos
	//y lo mismo para los jugadores pero recuerda que hay que malloquear los rects en en algun lado
}

static void		put_player_info(t_sdl *Graph, SDL_Surface *info_marc, t_data *data)
{
	int				tmp;
	int				y_pos;
	unsigned int	i;
	SDL_Surface		*tmp_surf;

	i = -1;
	while (++i < data->n_players)
	{
		tmp = 10;
		Graph->font[TMP_FONT].color = take_color(i);
		Graph->font[PLAYER_NBR_FONT].color = Graph->font[TMP_FONT].color;
		y_pos = Graph->square_info->h + 10 + info_marc->h * i;
		tmp_surf = ft_write_string(Graph, data->players[i].name, (int[2]){tmp, y_pos}, 0);
		y_pos += tmp_surf->h + 20;
		SDL_FreeSurface(tmp_surf);
		tmp_surf = ft_write_string(Graph, "Number of Lifes", (int[2]){tmp + (Graph->player_nbr->w * 10 - 9) / 2, y_pos}, 1);
		ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT], (int[2]){tmp, y_pos + tmp_surf->h}, Graph->player_nbr);
		tmp += Graph->player_nbr->w * 10 - 9 + 20;
		SDL_FreeSurface(tmp_surf);
		tmp_surf = ft_write_string(Graph, "Last Life", (int[2]){tmp + (Graph->player_nbr->w * 10 - 9) / 2, y_pos}, 1);
		ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT], (int[2]){tmp, y_pos + tmp_surf->h}, Graph->player_nbr);
		SDL_FreeSurface(tmp_surf);
	}
}

static void		ini_number(t_sdl *Graph, int mode, SDL_Surface **number)
{
	if (mode == GENERAL_NBR_FONT)
		*number = SDL_CreateRGBSurfaceWithFormat(0, 40, 60, 32, Graph->rack->format->format);
	else
		*number = SDL_CreateRGBSurfaceWithFormat(0, 30, 40, 32, Graph->rack->format->format);
	SDL_FillRect(*number, NULL, SDL_MapRGBA(Graph->rack->format, 255, 255, 255, 255));
	SDL_FillRect(*number, &(SDL_Rect){1, 1, (*number)->w - 2, (*number)->h - 2}, SDL_MapRGBA((*number)->format, 0, 0, 0, 255));
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
	ini_number(Graph, GENERAL_NBR_FONT, &Graph->general_nbr);
	put_general_info(Graph);
	ini_number(Graph, PLAYER_NBR_FONT, &Graph->player_nbr);
	put_player_info(Graph, info_marc, data);
}
