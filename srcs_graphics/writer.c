/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:42:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/28 18:23:32 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

SDL_Surface			*ft_write_string(char *str, int pos[2], int name)
{
	SDL_Surface *str_surf;
	SDL_Surface *tmp;

	if (!(tmp = TTF_RenderUTF8_Blended(g_Graph->font[TMP_FONT].font, str,
		g_Graph->font[TMP_FONT].color)))
		ft_SDL_error("TTF_RenderUTF8_Blended", MODE_TTF);
	if (!(str_surf = SDL_CreateRGBSurfaceWithFormat(0, tmp->w, tmp->h, 32,
		g_Graph->rack->format->format)))
		ft_SDL_error("SDL_CreateRGBSurfaceWithFormat", MODE_SDL);
	if (SDL_BlitSurface(tmp, NULL, str_surf, NULL))
		ft_SDL_error("SDL_BlitSurface", MODE_SDL);
	SDL_FreeSurface(tmp);
	ft_surf_to_text(g_Graph->info_text, str_surf,
		&(SDL_Rect){ft_abs(pos[0] - str_surf->w / 2 * name), pos[1],
		str_surf->w, str_surf->h});
	return (str_surf);
}

int				ft_write_number_fields(t_font *font, int pos[2],
		SDL_Surface *number)
{
	int		i;
	int		j;
	char	*pixel;
	int		pitch;
	SDL_Surface *tmp;

	tmp = TTF_RenderUTF8_Blended(font->font, "0", font->color);
	SDL_LockTexture(g_Graph->info_text, &(SDL_Rect){pos[0], pos[1], number->w * 10, number->h}, (void **)&pixel, &pitch);
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
	SDL_UnlockTexture(g_Graph->info_text);
	return (number->h);
}
