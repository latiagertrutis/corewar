/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_registers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 07:09:53 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/18 10:19:59 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	write_register(t_data *data, t_sdl *Graph, SDL_Surface *reg_square)
{
	int i;
	SDL_Rect num;
	SDL_Surface *reg_byte;
	SDL_Surface *tmp;

	i = 0;
	num.x = Graph->player_nbr->w * 2;
	num.y = 0;
	num.w = (reg_square->w - Graph->player_nbr->w * 2) / 4;
	num.h = reg_square->h;
	reg_byte = SDL_CreateRGBSurfaceWithFormat(0, num.w, num.h, 32, 372645892);
}

void	ft_ini_registers(t_data *data, t_sdl *Graph)
{
	SDL_Surface *reg_square;
	int			pitch;
	char		*pixel;
	int			j;

	reg_square = SDL_CreateRGBSurfaceWithFormat(0, Graph->player_nbr->w * 16, Graph->heart_pos->h, 32, 372645892);
//	SDL_FillRect(reg_square, &(SDL_Rect){0, 0, reg_square->w, reg_square->h}, 0xFF4D4D4D);
	SDL_FillRect(reg_square, &(SDL_Rect){0, 0, Graph->player_nbr->w * 2, reg_square->h}, 0xFF4D4D4D);
	ft_printf("reg square mide %i x %i\n", reg_square->w, reg_square->h);
//	SDL_FillRect(reg_square, &(SDL_Rect){2, 3, Graph->player_nbr->w * 2 - 4, reg_square->h - 5}, 0xFF000000);
	SDL_FillRect(reg_square, &(SDL_Rect){Graph->player_nbr->w * 2, 0, reg_square->w - Graph->player_nbr->w * 2, reg_square->h}, 0xFFFF0000);
	SDL_FillRect(reg_square, &(SDL_Rect){Graph->player_nbr->w * 2 + 5, 5, reg_square->w - Graph->player_nbr->w * 2 - 10, reg_square->h - 10}, 0xFFFFFFFF);

	SDL_LockTexture(Graph->info_text, &(SDL_Rect){Graph->heart_pos->x + Graph->heart_pos->w + 5, Graph->heart_pos->y, reg_square->w, reg_square->h}, (void **)&pixel, &pitch);
	SDL_LockSurface(reg_square);
	j = 0;
	while (++j < reg_square->h)
		memcpy(pixel + j * pitch, reg_square->pixels + j * reg_square->pitch, reg_square->pitch);
	SDL_UnlockSurface(reg_square);
	SDL_UnlockTexture(Graph->info_text);
	SDL_FreeSurface(reg_square);
}
