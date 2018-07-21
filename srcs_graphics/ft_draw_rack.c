/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:15:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/21 16:55:45 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	clean_field(t_sdl *Graph)
{
	if (SDL_SetRenderDrawColor(Graph->screen.Renderer, FIELD_COLOR
			SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	if (SDL_FillRect(Graph->screen.screen, &(SDL_Rect){0, 0, Graph->screen.w, Graph->screen.h}, 0x1C1C15FF))
		ft_SDL_error("SDL_FillRect", MODE_SDL);
	if (SDL_FillRect(Graph->screen.screen, &(SDL_Rect)
		{Graph->screen.w * RIGHT_BORDER,
		Graph->screen.h * UPPER_BORDER,
		Graph->screen.w - (Graph->screen.w * RIGHT_BORDER) -
			(Graph->screen.w * LEFT_BORDER),
		Graph->screen.h - (Graph->screen.h * UPPER_BORDER) -
			Graph->screen.h * BOTTOM_BORDER}, 0x3D3D33FF))
		ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
}

void		ft_draw_rack(t_data *data, SDL_Surface *screen)
{
	int		screen_w;
	int		screen_h;
	SDL_Surface *rack;
	char	*pixel;
	int		pitch;
	SDL_Texture *caca;
	SDL_Rect pene;
//	clean_field(data->arena->Graph);
	screen_w = data->arena->Graph->screen.w;
	screen_h = data->arena->Graph->screen.h;
	rack = data->arena->Graph->rack;
//	SDL_BlitSurface(rack, NULL, screen, &(SDL_Rect){screen_w * RIGHT_BORDER, screen_h * UPPER_BORDER, rack->w, rack->h});
//	SDL_BlitSurface(rack, NULL, screen, &(SDL_Rect){0, 0, rack->w, rack->h});
//	caca = SDL_CreateTextureFromSurface(data->arena->Graph->screen.Renderer, rack);
//	SDL_RenderCopy(data->arena->Graph->screen.Renderer, caca, NULL, &(SDL_Rect){data->arena->Graph->screen.w * RIGHT_BORDER, data->arena->Graph->screen.h * UPPER_BORDER, rack->w, rack->h});
//	SDL_RenderPresent(data->arena->Graph->screen.Renderer);
	pene = (SDL_Rect){0, 0, rack->w, rack->h};
//	ft_printf ("Antes pene mide %i x %i y esta en (%i, %i)\n", pene.w, pene.h, pene.x, pene.y);	
	SDL_LockTexture(data->arena->Graph->screen.texture, &pene, (void **)&pixel, &pitch);
//	ft_printf ("Despues pene mide %i x %i y esta en (%i, %i)\n", pene.w, pene.h, pene.x, pene.y);	
	SDL_LockSurface(rack);
//	for (int j = 0; j < rack->h; j++)
//	{
//		for (int i = 0; i < j * rack->pitch; i++)
//		{
//			pixel[i + j * rack->h] = ((int *)rack->pixels)[i];
//		}
//	}
	for(int j = 0; j < rack->h; j++)
		memcpy(pixel + j * pitch, rack->pixels + j * rack->pitch, rack->pitch);
//	SDL_UpdateTexture(data->arena->Graph->screen.texture, &pene, rack->pixels, rack->pitch);
	SDL_UnlockSurface(rack);
	SDL_UnlockTexture(data->arena->Graph->screen.texture);
}
