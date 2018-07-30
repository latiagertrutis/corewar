/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:42:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/29 21:38:03 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

SDL_Surface			*ft_write_string(t_sdl *Graph, char *str, int pos[2], int name)
{
	SDL_Surface *str_surf;
	SDL_Surface *tmp;
	char		*pixel;
	int			pitch;
	int			i;

	tmp = TTF_RenderUTF8_Blended(Graph->font[TMP_FONT].font, str, Graph->font[TMP_FONT].color);
	str_surf = SDL_CreateRGBSurfaceWithFormat(0, tmp->w, tmp->h, 32, Graph->rack->format->format);
	SDL_BlitSurface(tmp, NULL, str_surf, NULL);
	SDL_FreeSurface(tmp);
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){ft_abs(pos[0] - str_surf->w / 2 * name), pos[1], str_surf->w, str_surf->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(str_surf);
	i = -1;
	while (++i < str_surf->h)
		memcpy(pixel + i * pitch, str_surf->pixels + i * str_surf->pitch, str_surf->pitch);
	SDL_UnlockSurface(str_surf);
	SDL_UnlockTexture(Graph->info_text);
	return (str_surf);
}

int				ft_write_number_fields(t_sdl *Graph, t_font *font, int pos[2], SDL_Surface *number)
{
	int		i;
	int		j;
	char	*pixel;
	int		pitch;
	SDL_Surface *tmp;

	tmp = TTF_RenderUTF8_Blended(font->font, "0", font->color);
	SDL_LockTexture(Graph->info_text, &(SDL_Rect){pos[0], pos[1], number->w * 10, number->h}, (void **)&pixel, &pitch);
	SDL_FillRect(number, &(SDL_Rect){1, 1, number->w - 2, number->h - 2}, SDL_MapRGBA(number->format, 0, 0, 0, 255));
	i = 0;
	SDL_BlitSurface(tmp, NULL, number, &(SDL_Rect){(number->w - tmp->w) / 2, (number->h - tmp->h) / 2 + 2, tmp->w, tmp->h});
	SDL_LockSurface(number);
	while (i < 10)
	{
		j = -1;
		while (++j < number->h)
			memcpy(pixel + i * (number->pitch - 4) + j * pitch, number->pixels + j * number->pitch, number->pitch);
		i++;
	}
	SDL_UnlockSurface(number);
	SDL_UnlockTexture(Graph->info_text);
	return (number->h);
}
