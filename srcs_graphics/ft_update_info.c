/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:39:44 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/10 17:17:07 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		copy_to_texture(SDL_Texture *text, SDL_Surface *surf,
		SDL_Rect *pos)
{
	char	*pixel;
	int		pitch;
	int		j;

	SDL_LockTexture(text, pos, (void **)&pixel, &pitch);
	SDL_LockSurface(surf);
	j = 0;
	while (++j < surf->h)
		memcpy(pixel + j * pitch, surf->pixels + j * surf->pitch, surf->pitch);
	SDL_UnlockSurface(surf);
	SDL_UnlockTexture(text);
}

static void		update_digit(SDL_Rect pos, t_sdl *Graph, char digit[2],
		int mode)
{
	SDL_Surface	*tmp;
	t_font		font;
	SDL_Surface *num_surf;

	if (mode == GENERAL_NBR_FONT)
		num_surf = Graph->general_nbr;
	else
		num_surf = Graph->player_nbr;
	font = Graph->font[mode];
	tmp = TTF_RenderUTF8_Blended(font.font, digit, font.color);
	SDL_FillRect(num_surf, &(SDL_Rect){1, 1, num_surf->w - 2, num_surf->h - 2},
		SDL_MapRGBA(num_surf->format, 0, 0, 0, 255));
	SDL_BlitSurface(tmp, NULL, num_surf, &(SDL_Rect){(num_surf->w - tmp->w) / 2,
		(num_surf->h - tmp->h) / 2 + 2, tmp->w, tmp->h});
	copy_to_texture(Graph->info_text, num_surf, &pos);
	SDL_FreeSurface(tmp);
}

static void		update_cicles(t_sdl *Graph, unsigned int cicles, SDL_Rect pieze)
{
	int				pos;
	SDL_Surface		*tmp;
	char			*digits;

	digits = "0123456789";
	if (cicles % 10)
		update_digit((SDL_Rect){pieze.x + 9 * (pieze.w - 1), pieze.y, pieze.w,
			pieze.h}, Graph, (char[2]){digits[cicles % 10], 0},
			GENERAL_NBR_FONT);
	else if (cicles > 0)
	{
		pos = 1;
		while (cicles > 0)
		{
			update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
					pieze.y, pieze.w, pieze.h}, Graph,
				(char[2]){digits[cicles % 10], 0}, GENERAL_NBR_FONT);
			cicles /= 10;
			pos++;
		}
	}
}

static void		update_ctd_pcs_plyrs(t_sdl *Graph, unsigned int info,
			SDL_Rect pieze, int mode)
{
	int		pos;
	char	*digits;

	digits = "0123456789";
	pos = 1;
	while (info > 0)
	{
		update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
				pieze.y, pieze.w, pieze.h}, Graph,
			(char[2]){digits[info % 10], 0}, mode);
		if (!(info /= 10))
			return ;
		pos++;
	}
	while (pos < 10)
	{
		update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
				pieze.y, pieze.w, pieze.h}, Graph, "0\0", mode);
		pos++;
	}
}

void	ft_update_info(t_sdl *Graph, t_data *data, int cicle_pre_die)
{
	static unsigned int	nbr_pcs = 0;
	int					i;

//	update_cicles(Graph, data->nb_cycles, *Graph->info.cicles_gen);
	update_ctd_pcs_plyrs(Graph, data->nb_cycles, *Graph->info.cicles_gen, GENERAL_NBR_FONT);
	if (!cicle_pre_die || data->mods->dump)
	{
		update_ctd_pcs_plyrs(Graph, 0,
			*Graph->info.cicle_to_die, GENERAL_NBR_FONT);
		update_ctd_pcs_plyrs(Graph, data->cycle_to_die,
			*Graph->info.cicle_to_die, GENERAL_NBR_FONT);
	}
	if (nbr_pcs != data->nb_pc)
	{
		update_ctd_pcs_plyrs(Graph, data->nb_pc_active, *Graph->info.processos,
			GENERAL_NBR_FONT);
		nbr_pcs = data->nb_pc;
	}
	i = 0;
	while (i < data->n_players)
	{
		Graph->font[PLAYER_NBR_FONT].color = ft_SDL_color(i);
		if (!cicle_pre_die)
			update_ctd_pcs_plyrs(Graph, 0, Graph->info.cicles_play[i],
					PLAYER_NBR_FONT);
		if (data->players[i].live_call)
		{
			update_ctd_pcs_plyrs(Graph, data->players[i].live_counter,
					Graph->info.cicles_play[i], PLAYER_NBR_FONT);
			update_ctd_pcs_plyrs(Graph, data->players[i].last_live,
				Graph->info.lst_life[i], PLAYER_NBR_FONT);
			data->players[i].live_call = 0;
		}
		i++;
	}
}
