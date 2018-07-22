/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:27:44 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/21 21:38:25 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void ft_quit_graphics(t_sdl *Game)
{
	SDL_FreeSurface(Game->screen.screen);	
	SDL_FreeSurface(Game->rack_square);
	SDL_FreeSurface(Game->rack);
	SDL_DestroyTexture(Game->screen.texture);
	SDL_DestroyRenderer(Game->screen.Renderer);
	SDL_DestroyWindow(Game->screen.window);
	TTF_Quit();
	SDL_Quit();
	free(Game);
}
