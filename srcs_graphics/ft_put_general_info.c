/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_general_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 10:20:06 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/01 10:20:44 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		prepare_font(t_sdl *Graph, int nbr_font, SDL_Color color)
{
	t_font	*font;
	t_font	*ref_font;

	font = &(Graph->font[nbr_font]);
	ref_font = &(Graph->font[FIELD_FONT]);
	font->font_size = ref_font->font_size * 2;
	font->font = TTF_OpenFont("./whitrabt.ttf", font->font_size);
	TTF_SizeUTF8(font->font, "A", &font->w, &font->h);
	font->color = color;
}

static int		prepare_string(int pos[2], t_sdl *Graph, char *str, int mode)
{
	SDL_Surface *tmp_surf;
	int			tmp;

	tmp_surf = ft_write_string(Graph, str, pos, mode);
	tmp = tmp_surf->h;
	SDL_FreeSurface(tmp_surf);
		return (tmp);
}

void		ft_put_general_info(t_sdl *Graph)
{
	int			tmp;
	int			x_pos;

	prepare_font(Graph, TMP_FONT, (SDL_Color){255, 255, 255, 255});
	x_pos = 50;
	Graph->font[GENERAL_NBR_FONT].color = Graph->font[TMP_FONT].color;
	tmp = 15;
	tmp += prepare_string((int[2]){x_pos + (Graph->general_nbr->w * 10 - 9)
			/ 2, tmp}, Graph, "Number of Cycles", 1);
	*Graph->info.cicles_gen = (SDL_Rect){x_pos, tmp, Graph->info.cicles_gen->w,
		Graph->info.cicles_gen->h};
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT],
			(int[2]){x_pos, tmp}, Graph->general_nbr) + 10;
	tmp += prepare_string((int[2]){x_pos + (Graph->general_nbr->w * 10 - 9)
			/ 2, tmp}, Graph, "Cycles to Die", 1);
	*Graph->info.cicle_to_die = (SDL_Rect){x_pos, tmp,
			Graph->info.cicles_gen->w, Graph->info.cicles_gen->h};
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT],
			(int[2]){x_pos, tmp}, Graph->general_nbr) + 10;
	tmp += prepare_string((int[2]){x_pos + (Graph->general_nbr->w * 10 - 9)
			/ 2, tmp}, Graph, "Number of Processos", 1);
	*Graph->info.processos = (SDL_Rect){x_pos, tmp, Graph->info.cicles_gen->w,
			Graph->info.cicles_gen->h};
	tmp += ft_write_number_fields(Graph, &Graph->font[GENERAL_NBR_FONT],
			(int[2]){x_pos, tmp}, Graph->general_nbr);
}
