/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:39:44 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/08/04 18:22:39 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		copy_to_texture(SDL_Texture *text, SDL_Surface *surf, SDL_Rect *pos)
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

static void		update_digit(SDL_Rect pos, t_sdl *Graph, char digit[2])
{
	SDL_Surface	*tmp;
	t_font		font;
	SDL_Surface *num_surf;

	num_surf = Graph->general_nbr;
	font = Graph->font[GENERAL_NBR_FONT];
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
				pieze.h}, Graph, (char[2]){digits[cicles % 10], 0});
	else if (cicles > 0)
	{
		pos = 1;
		while (cicles > 0)
		{
			update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
					pieze.y, pieze.w, pieze.h}, Graph,
					(char[2]){digits[cicles % 10], 0});
			cicles /= 10;
			pos++;
		}
	}
}

static void		update_ctd_pcs(t_sdl *Graph, unsigned int ctd, SDL_Rect pieze)
{
	int		pos;
	char	*digits;

	digits = "0123456789";
	pos = 1;
	while (ctd > 0)
	{
		update_digit((SDL_Rect){pieze.x + (10 - pos) * (pieze.w - 1),
				pieze.y, pieze.w, pieze.h}, Graph,
				(char[2]){digits[ctd % 10], 0});
		ctd /= 10;
		pos++;
	}
}

void	ft_update_info(t_sdl *Graph, t_data *data, int cicle_pre_die)
{
	static unsigned int	nbr_pcs = 0;
	int					i;

	update_cicles(Graph, data->nb_cycles, *Graph->info.cicles_gen);
	if (!cicle_pre_die)
		update_ctd_pcs(Graph, data->cycle_to_die, *Graph->info.cicle_to_die);
	if (nbr_pcs != data->nb_pc)
	{
		update_ctd_pcs(Graph, data->nb_pc_active, *Graph->info.processos);
		nbr_pcs = data->nb_pc;
	}
//	i = 0;
//	while (i < data->n_players)
//	{
//
//	}
}
