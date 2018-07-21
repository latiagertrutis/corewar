/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board_to_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 04:10:37 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/21 22:36:22 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_board_to_screen(t_sdl *Graph, t_arena *arena)
{
	int			i;
	char		*pixel;
	int			pitch;

	i = 0;

	SDL_LockTexture(Graph->screen.texture, NULL, (void **)&pixel, &pitch);
	while (i < MEM_SIZE)
	{
		ft_write_byte(i, arena, pixel, pitch);
		i++;
	}
	SDL_UnlockTexture(Graph->screen.texture);
//	SDL_SetColorKey(Graph->rack, SDL_TRUE, SDL_MapRGBA(Graph->rack->format, 0, 0, 0, 255));
//	SDL_LockTexture(Graph->screen.texture, &(SDL_Rect){Graph->screen.w * RIGHT_BORDER, Graph->screen.h * UPPER_BORDER, Graph->rack->w, Graph->rack->h}, (void **)&pixel, &pitch);
//	SDL_LockSurface(Graph->rack);
//	for(int j = 0; j < Graph->rack->h; j++)
//		memcpy(pixel + j * pitch, Graph->rack->pixels + j * Graph->rack->pitch, Graph->rack->pitch);
//	SDL_UnlockSurface(Graph->rack);
//	SDL_UnlockTexture(Graph->screen.texture);
}
