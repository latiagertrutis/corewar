/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:27:44 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/24 22:44:19 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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

void ft_quit_graphics(void)
{
	destroy_hex_array(g_Graph->hexa_bytes);
	SDL_FreeSurface(g_Graph->rack);
	SDL_DestroyTexture(g_Graph->screen.texture);
	SDL_DestroyRenderer(g_Graph->screen.Renderer);
	SDL_DestroyWindow(g_Graph->screen.window);
	TTF_Quit();
	SDL_Quit();
	free(g_Graph);
}
