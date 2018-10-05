/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:43:28 by jagarcia          #+#    #+#             */
/*   Updated: 2018/10/05 18:29:47 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	mouse_event(SDL_Event e, int mode)
{
	if (mode > 0 && SDL_PointInRect(&(SDL_Point){e.button.x, e.button.y},
		&(SDL_Rect){g_graph->pause_pos->x + g_graph->screen.w *
		RIGHT_BORDER + g_graph->big_square->w + 20, g_graph->pause_pos->y
		+ g_graph->screen.h * UPPER_BORDER, g_graph->pause_pos->w,
		g_graph->pause_pos->h}))
		g_pause = ft_pause_button(g_pause);
	else if (SDL_PointInRect(&(SDL_Point){e.button.x, e.button.y},
		&(SDL_Rect){g_graph->button_pos->x + g_graph->screen.w *
		RIGHT_BORDER + g_graph->big_square->w + 20, g_graph->button_pos->y
		+ g_graph->screen.h * UPPER_BORDER, g_graph->button_pos->w,
		g_graph->button_pos->h}))
		ft_back_forw_buttons(1 * mode);
	else if (SDL_PointInRect(&(SDL_Point){e.button.x, e.button.y},
		&(SDL_Rect){g_graph->button_pos->x + g_graph->button_pos->w +
		g_graph->screen.w * RIGHT_BORDER + g_graph->big_square->w + 20,
		g_graph->button_pos->y + g_graph->screen.h * UPPER_BORDER,
		g_graph->button_pos->w, g_graph->button_pos->h}))
		ft_back_forw_buttons(2 * mode);
}

static void	key_event(SDL_Event event, int *running)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		*running = SDL_FALSE;
	else if (event.key.keysym.sym == SDLK_SPACE)
		g_pause = ft_pause_button(g_pause);
	else if (event.key.keysym.sym == SDLK_RIGHT)
		g_step = 1;
	else if (event.key.keysym.sym == SDLK_i)
		g_hexl = g_hexl ? 0 : 1;
	else if (event.key.keysym.sym == SDLK_KP_PLUS)
	{
		g_cycle_cuant++;
		ft_update_little_screen();
	}
	else if (event.key.keysym.sym == SDLK_KP_MINUS)
	{
		g_cycle_cuant = (g_cycle_cuant == 1) ? 1 : g_cycle_cuant - 1;
		ft_update_little_screen();
	}
}

void		ft_events(int *running)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			*running = SDL_FALSE;
		else if (event.type == SDL_KEYDOWN)
			key_event(event, running);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				mouse_event(event, 1);
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
			if (event.button.button == SDL_BUTTON_LEFT)
				mouse_event(event, -1);
	}
}
