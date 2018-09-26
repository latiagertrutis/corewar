/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:28:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/26 17:17:19 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	prepare_all_sprites(int dim, SDL_Surface *sprite)
{
	int i;
	int pos;
	SDL_Rect pos_in_sprite;

	i = -1;
	pos = 1;
	pos_in_sprite = (SDL_Rect){2, 1, 76, 69};
	while (++i < 6)
	{
		if (!(pos % 2))
		{
//			pos_in_sprite = (SDL_Rect){2, 1 + (pos - 1) * (69 + 1), 76, 69};
			pos_in_sprite.y += 73; //69 + 4
			pos_in_sprite.x -= 80; // 76 + 4
		}
		else
			pos_in_sprite.x += 80;

//			pos_in_sprite = (SDL_Rect){2 + 76 + 4, 1 + (pos - 1) * (69 + 1), 76, 69};
		g_Graph->heart[pos] = SDL_CreateRGBSurfaceWithFormat(0, dim + 7, dim, 32, 372645892);
		SDL_BlitScaled(sprite, &pos_in_sprite, g_Graph->heart[pos++], NULL);
	}
}

void	ft_ini_sprites(void)
{
	SDL_RWops *tmp;
	SDL_Surface *sprite;
	int disp_space_y;
	int disp_space_x;
	int i;

	if (!(g_Graph->heart = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * 7)))
		ft_error("malloc ft_ini_sprites");
	if (!(tmp = SDL_RWFromFile("./heart.png", "rb")))
		ft_SDL_error("SDL_RWFromFile", MODE_SDL);
	if (!(sprite = IMG_LoadPNG_RW(tmp)))
		ft_SDL_error("IMG_LoadPNG_RW", MODE_IMG);
	if (!(g_Graph->heart_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc ft_ini_sprites 2");
	i = 1; 
	disp_space_y = (g_Graph->info_marc->h - ((g_Graph->info.cicles_play[0].y + g_Graph->info.cicles_play[0].h) - (g_Graph->info_marc->y)));
	disp_space_x = g_Graph->player_nbr->w * 20;
	while (!g_Graph->heart[0] || (disp_space_y - g_Graph->heart[0]->h > 20 && g_Graph->heart[0]->h < disp_space_y && disp_space_x > g_Graph->heart[0]->w * 4))
	{
		if (g_Graph->heart[0])
			SDL_FreeSurface(g_Graph->heart[0]);
		g_Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
		SDL_FillRect(g_Graph->heart[0], NULL, 0xFF00FF00);
		SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, g_Graph->heart[0], NULL);
		i++;
	}
	i--;
	SDL_FreeSurface(g_Graph->heart[0]);
	g_Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
	SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, g_Graph->heart[0], NULL);
//	SDL_BlitScaled(sprite, &(SDL_Rect){2, 1 + 73, 76, 69}, g_Graph->heart[0], NULL);
	*g_Graph->heart_pos = (SDL_Rect){g_Graph->info.cicles_play[0].x, ((g_Graph->info_marc->h - ((g_Graph->info.cicles_play[0].y + g_Graph->info.cicles_play[0].h) - (g_Graph->info_marc->y))) - g_Graph->heart[0]->h) / 2 + g_Graph->info.cicles_play[0].y + g_Graph->info.cicles_play[0].h, g_Graph->heart[0]->w, g_Graph->heart[0]->h};
	prepare_all_sprites(i, sprite);
	i = 0;
	while (i < g_n_players)
		ft_reset_health(i++);
}

void	ft_reset_health(int player)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	int j;
	int i;
	int dist;

	dist = (g_Graph->player_nbr->w * 20 - g_Graph->heart_pos->w * 4) / 3 + g_Graph->heart_pos->w;
	i = 0;
	while (i < 4)
	{
		heart = (SDL_Rect){g_Graph->heart_pos->x + dist * i++, g_Graph->heart_pos->y + (g_Graph->info_marc->h) * player, g_Graph->heart[0]->w, g_Graph->heart[0]->h};
		SDL_LockTexture(g_Graph->info_text, &heart, (void **)&pixel, &pitch);
		SDL_LockSurface(g_Graph->heart[0]);
		j = 0;
		while (++j < g_Graph->heart[0]->h)
			memcpy(pixel + j * pitch, g_Graph->heart[0]->pixels + j * g_Graph->heart[0]->pitch, g_Graph->heart[0]->pitch);
		SDL_UnlockSurface(g_Graph->heart[0]);
		SDL_UnlockTexture(g_Graph->info_text);
	}
}

void	ft_check_health(const int cycle_to_die, int player, int cicle_pre_die)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	static int top[4] = {0, 0, 0, 0};
	int j;
	int i;
	int pos;
	int dist;

	i = 0;
	if (!top[player])
		top[player] = cycle_to_die;
	dist = (g_Graph->player_nbr->w * 20 - g_Graph->heart_pos->w * 4) / 3 + g_Graph->heart_pos->w;
	if (g_players[player].live_counter)
	{
		top[player] = cycle_to_die;
		ft_reset_health(player);
		return ;
	}
	while (cicle_pre_die <= top[player] && i < 4)
	{
		pos = cicle_pre_die * 7 * 4 / top[player];
		if ((pos + 1) > i * 7 && (pos + 1) <= (i + 1) * 7)
		{
			pos -= i * 7;
			heart = (SDL_Rect){g_Graph->heart_pos->x + dist * i, g_Graph->heart_pos->y + (g_Graph->info_marc->h) * player, g_Graph->heart[pos]->w, g_Graph->heart[pos]->h};
			SDL_LockTexture(g_Graph->info_text, &heart, (void **)&pixel, &pitch);
			SDL_LockSurface(g_Graph->heart[pos]);
			j = 0;
			while (++j < g_Graph->heart[pos]->h)
				memcpy(pixel + j * pitch, g_Graph->heart[pos]->pixels + j * g_Graph->heart[pos]->pitch, g_Graph->heart[pos]->pitch);
			SDL_UnlockSurface(g_Graph->heart[pos]);
			SDL_UnlockTexture(g_Graph->info_text);
		}
		i++;
	}
}
