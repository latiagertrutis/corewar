/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_player_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 10:18:26 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/01 10:23:34 by mrodrigu         ###   ########.fr       */
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

static int		prepare_string(int pos[2], t_sdl *Graph, char *str, int mode)
{
	SDL_Surface *tmp_surf;
	int			tmp;

	tmp_surf = ft_write_string(Graph, str, pos, mode);
	tmp = tmp_surf->h;
	SDL_FreeSurface(tmp_surf);
		return (tmp);
}

void		ft_put_player_info(t_sdl *Graph, SDL_Surface *info_marc,
		                t_data *data, int i)
{
	int				tmp;
	int				y_pos;
	int				tmp2;

	tmp = 10;
	Graph->font[TMP_FONT].color = take_color(i);
	Graph->font[PLAYER_NBR_FONT].color = Graph->font[TMP_FONT].color;
	y_pos = Graph->square_info->h + 10 + info_marc->h * i;
	y_pos += prepare_string((int[2]){tmp,y_pos}, Graph,
			data->players[i].name, 0) + 20;
	tmp2 = prepare_string((int[2]){tmp + (Graph->player_nbr->w * 10 - 9)
			/ 2, y_pos }, Graph, "Number of Lifes", 1);
	ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT],
			(int[2]){tmp, y_pos + tmp2}, Graph->player_nbr);
	Graph->info.cicles_play[i] = (SDL_Rect){tmp, y_pos + tmp2,
			Graph->info.cicles_play[i].w, Graph->info.cicles_play[i].h};
	tmp += Graph->player_nbr->w * 10 - 9 + 20;
	tmp2 = prepare_string((int[2]){tmp + (Graph->player_nbr->w * 10 - 9)
			/ 2, y_pos}, Graph, "Last Life", 1);
	ft_write_number_fields(Graph, &Graph->font[PLAYER_NBR_FONT],
			(int[2]){tmp, y_pos + tmp2}, Graph->player_nbr);
	Graph->info.lst_life[i] = (SDL_Rect){tmp, y_pos + tmp2,
			Graph->info.lst_life[i].w, Graph->info.lst_life[i].h};
}
