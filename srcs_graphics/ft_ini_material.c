/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_data_surfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:02:57 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/26 00:44:41 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		put_general_info(t_data *data, t_sdl *Graph)
{
	SDL_Surface *noc;
	SDL_Surface *ctd;
//	SDL_Surface *hall_9000;
	SDL_Surface *tmp;
	SDL_Color	color;
	char		*pixel;
	int			pitch;
	int			i;

	color = (SDL_Color){FIELD_COLOR SDL_ALPHA_OPAQUE};
	tmp = TTF_RenderUTF8_Blended(Graph->font[1].font, "Number of Cycles: ", color);
	noc = SDL_CreateRGBSurfaceWithFormat(0, tmp->w, tmp->h, 32, Graph->rack->format->format);
	SDL_BlitSurface(tmp, NULL, noc, NULL);
	SDL_FreeSurface(tmp);
	tmp = TTF_RenderUTF8_Blended(Graph->font[1].font, "Cicles to die: ", color);
	ctd = SDL_CreateRGBSurfaceWithFormat(0, tmp->w, tmp->h, 32, Graph->rack->format->format);
	SDL_BlitSurface(tmp, NULL, ctd, NULL);

	SDL_LockTexture(Graph->info_text, &(SDL_Rect){10, 10 + noc->h, ctd->w, ctd->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(ctd);
	i = 0;
	while (++i < ctd->h)
		memcpy(pixel + i * pitch, ctd->pixels + i * ctd->pitch, ctd->pitch);
	SDL_UnlockSurface(ctd);
	SDL_UnlockTexture(Graph->info_text);
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){10, 10, noc->w, noc->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(noc);
	i = 0;
	while (++i < noc->h)
		memcpy(pixel + i * pitch, noc->pixels + i * noc->pitch, noc->pitch);
	SDL_UnlockSurface(noc);
	SDL_UnlockTexture(Graph->info_text);
	SDL_FreeSurface(ctd);
	SDL_FreeSurface(noc);
}

void	ft_ini_material(t_data *data, t_sdl *Graph)
{

	Graph->font[1].font_size = Graph->font[0].font_size * 2;
	Graph->font[1].font = TTF_OpenFont("./Ubuntu-B.ttf", Graph->font[1].font_size);
	TTF_SizeUTF8(Graph->font[1].font, "A", &Graph->font[1].w, &Graph->font[1].h);
	put_general_info(data, Graph);
}
