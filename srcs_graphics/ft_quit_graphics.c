/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:27:44 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/24 18:35:55 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		destroy_hex_array(SDL_Surface ***hex_array)
{
	int i;
	int j;
	int k;
	
	k = 0;
	while (k < 9)
	{
		i = 0;
		while (i < 16)
		{
			j = 0;
			while (j < 16)
			{
				SDL_FreeSurface(hex_array[k][i * 16 + j]);
				j++;
			}
			i++;
		}
		free(hex_array[k]);
		k++;
	}
	free(hex_array);
}

void ft_quit_graphics(t_sdl *Game)
{
	destroy_hex_array(Game->hexa_bytes);
	SDL_FreeSurface(Game->rack);
	SDL_DestroyTexture(Game->screen.texture);
	SDL_DestroyRenderer(Game->screen.Renderer);
	SDL_DestroyWindow(Game->screen.window);
	TTF_Quit();
	SDL_Quit();
	free(Game);
}
