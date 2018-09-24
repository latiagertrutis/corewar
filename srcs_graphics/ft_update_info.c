/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:39:44 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/24 22:42:17 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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

static void		update_digit(SDL_Rect pos, t_sdl *g_Graph, char digit[2],
		int mode)
{
	SDL_Surface	*tmp;
	t_font		font;
	SDL_Surface *num_surf;

	if (mode == GENERAL_NBR_FONT)
		num_surf = g_Graph->general_nbr;
	else
		num_surf = g_Graph->player_nbr;
	font = g_Graph->font[mode];
	tmp = TTF_RenderUTF8_Blended(font.font, digit, font.color);
	SDL_FillRect(num_surf, &(SDL_Rect){1, 1, num_surf->w - 2, num_surf->h - 2},
		SDL_MapRGBA(num_surf->format, 0, 0, 0, 255));
	SDL_BlitSurface(tmp, NULL, num_surf, &(SDL_Rect){(num_surf->w - tmp->w) / 2,
		(num_surf->h - tmp->h) / 2 + 2, tmp->w, tmp->h});
	copy_to_texture(g_Graph->info_text, num_surf, &pos);
	SDL_FreeSurface(tmp);
}

static void		update_ctd_pcs_plyrs(unsigned int info, SDL_Rect pieze, int mode)
{
	int		pos;
	char	*digits;

	digits = "0123456789";
	pos = 1;
	while (info > 0)
	{
		update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
				pieze.y, pieze.w, pieze.h}, g_Graph,
			(char[2]){digits[info % 10], 0}, mode);
		if (!(info /= 10))
			return ;
		pos++;
	}
	while (pos < 10)
	{
		update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
				pieze.y, pieze.w, pieze.h}, g_Graph, "0\0", mode);
		pos++;
	}
}

static void	place_health(int player, int h)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	int j;
	
	heart = (SDL_Rect){g_Graph->heart_pos->x, g_Graph->heart_pos->y + (g_Graph->info_marc->h) * player, g_Graph->heart[h]->w, g_Graph->heart[h]->h};
	SDL_LockTexture(g_Graph->info_text, &heart, (void **)&pixel, &pitch);
	SDL_LockSurface(g_Graph->heart[h]);
	j = 0;
	while (++j < g_Graph->heart[h]->h)
		memcpy(pixel + j * pitch, g_Graph->heart[h]->pixels + j * g_Graph->heart[h]->pitch, g_Graph->heart[h]->pitch);
	SDL_UnlockSurface(g_Graph->heart[h]);
	SDL_UnlockTexture(g_Graph->info_text);
}

void	ft_update_info(const t_player *players, const int cicle_pre_die)
{
	static unsigned int	nbr_pcs = 0;
	static unsigned int lives[MAX_PLAYERS] = {0};
	unsigned int		i;

//	if (!cicle_pre_die)
//		ft_reset_health(data, g_Graph, 0);
//	place_health(data, g_Graph, 0, 2);
//	else
//	ft_reset_health(data, g_Graph, 1);
//	ft_reset_health(data, g_Graph, 2);
//	ft_reset_health(data, g_Graph, 3);
	update_ctd_pcs_plyrs(g_frame->cycle, *g_Graph->info.cicles_gen, GENERAL_NBR_FONT);
	if (!cicle_pre_die)// || data->mods->dump)
	{
		update_ctd_pcs_plyrs(0,
			*g_Graph->info.cicle_to_die, GENERAL_NBR_FONT);
		update_ctd_pcs_plyrs(g_frame->cycle_to_die,
			*g_Graph->info.cicle_to_die, GENERAL_NBR_FONT);
	}
	if (nbr_pcs != g_frame->nb_pc)
	{
		if (nbr_pcs > g_frame->nb_pc)
			update_ctd_pcs_plyrs(0,
				*g_Graph->info.processos, GENERAL_NBR_FONT);
		update_ctd_pcs_plyrs(g_frame->nb_pc, *g_Graph->info.processos,
			GENERAL_NBR_FONT);
		nbr_pcs = g_frame->nb_pc;
	}
	i = 0;
	while (i < g_n_players)
	{
		ft_check_health(g_frame->cycle_to_die, i, cicle_pre_die);
		g_Graph->font[PLAYER_NBR_FONT].color = ft_SDL_color(i);
		if (!cicle_pre_die)
			update_ctd_pcs_plyrs(0, g_Graph->info.cicles_play[i],
					PLAYER_NBR_FONT);
		if (players[i].live_counter != lives[i])
		{
			update_ctd_pcs_plyrs(players[i].live_counter,
					g_Graph->info.cicles_play[i], PLAYER_NBR_FONT);
			update_ctd_pcs_plyrs(players[i].last_live,
				g_Graph->info.lst_life[i], PLAYER_NBR_FONT);
			lives[i] = players[i].live_counter;
		}
		i++;
	}
}
