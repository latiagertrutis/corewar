/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:15:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/20 10:43:18 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	clean_field(t_sdl *Graph)
{
		if (SDL_SetRenderDrawColor(Graph->screen.Renderer, FIELD_COLOR
			SDL_ALPHA_OPAQUE))
		ft_SDL_error("SDL_SetRenderDrawColor", MODE_SDL);
	if (SDL_FillRect(Graph->screen.screen, &(SDL_Rect)
		{Graph->screen.w * RIGHT_BORDER,
		Graph->screen.h * UPPER_BORDER,
		Graph->screen.w - (Graph->screen.w * RIGHT_BORDER) -
			(Graph->screen.w * LEFT_BORDER),
		Graph->screen.h - (Graph->screen.h * UPPER_BORDER) -
			Graph->screen.h * BOTTOM_BORDER}, 0x3D3D33FF))
		ft_SDL_error("SDL_RenderDrawRect", MODE_SDL);
		/* SDL_RenderFillRect(Graph->screen.Renderer, &(SDL_Rect) */
		/* 	{Graph->screen.w * RIGHT_BORDER, */
		/* 	Graph->screen.h * UPPER_BORDER, */
		/* 	Graph->screen.w - (Graph->screen.w * RIGHT_BORDER) - */
		/* 	(Graph->screen.w * LEFT_BORDER), */
		/* 	Graph->screen.h - (Graph->screen.h * UPPER_BORDER) - */
		/* 	Graph->screen.h * BOTTOM_BORDER}); */
}

void		ft_draw_rack(t_data *data, SDL_Surface *screen)
{
	int		screen_w;
	int		screen_h;
	SDL_Surface *rack;

	//	clean_field(Graph);
	screen_w = data->arena->Graph->screen.w;
	screen_h = data->arena->Graph->screen.h;
	rack = data->arena->Graph->rack;
	SDL_BlitSurface(rack, NULL, screen, &(SDL_Rect){screen_w * RIGHT_BORDER,
		screen_h * UPPER_BORDER, screen_w - (screen_w * RIGHT_BORDER) -
		(screen_w * LEFT_BORDER), screen_h - (screen_h * UPPER_BORDER) -
		screen_h * BOTTOM_BORDER});
}
