/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:28:52 by jagarcia          #+#    #+#             */
/*   Updated: 2018/09/24 16:56:35 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	prepare_all_sprites(t_sdl *Graph, int dim, SDL_Surface *sprite)
{
	int i;
	int pos;
	SDL_Rect pos_in_sprite;
	int	mod_hori;

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
		Graph->heart[pos] = SDL_CreateRGBSurfaceWithFormat(0, dim + 7, dim, 32, 372645892);
		SDL_BlitScaled(sprite, &pos_in_sprite, Graph->heart[pos++], NULL);
	}
}

void	ft_ini_sprites(t_data *data, t_sdl *Graph)
{
	SDL_RWops *tmp;
	SDL_Surface *sprite;
	int disp_space_y;
	int disp_space_x;
	int i;

	if (!(Graph->heart = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * 7)))
		ft_error("malloc ft_ini_sprites");
	if (!(tmp = SDL_RWFromFile("./heart.png", "rb")))
		ft_SDL_error("SDL_RWFromFile", MODE_SDL);
	if (!(sprite = IMG_LoadPNG_RW(tmp)))
		ft_SDL_error("IMG_LoadPNG_RW", MODE_IMG);
	if (!(Graph->heart_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		ft_error("malloc ft_ini_sprites 2");
	i = 1; 
	disp_space_y = (Graph->info_marc->h - ((Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h) - (Graph->info_marc->y)));
	disp_space_x = Graph->player_nbr->w * 20;
	while (!Graph->heart[0] || (disp_space_y - Graph->heart[0]->h > 20 && Graph->heart[0]->h < disp_space_y && disp_space_x > Graph->heart[0]->w * 4))
	{
		if (Graph->heart[0])
			SDL_FreeSurface(Graph->heart[0]);
		Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
		SDL_FillRect(Graph->heart[0], NULL, 0xFF00FF00);
		SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, Graph->heart[0], NULL);
		i++;
	}
	i--;
	SDL_FreeSurface(Graph->heart[0]);
	Graph->heart[0] = SDL_CreateRGBSurfaceWithFormat(0, i + 7, i, 32, 372645892);
	SDL_BlitScaled(sprite, &(SDL_Rect){2, 1, 76, 69}, Graph->heart[0], NULL);
//	SDL_BlitScaled(sprite, &(SDL_Rect){2, 1 + 73, 76, 69}, Graph->heart[0], NULL);
	*Graph->heart_pos = (SDL_Rect){Graph->info.cicles_play[0].x, ((Graph->info_marc->h - ((Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h) - (Graph->info_marc->y))) - Graph->heart[0]->h) / 2 + Graph->info.cicles_play[0].y + Graph->info.cicles_play[0].h, Graph->heart[0]->w, Graph->heart[0]->h};
	prepare_all_sprites(Graph, i, sprite);
	ft_reset_health(data, Graph, 0);
	ft_reset_health(data, Graph, 1);
	ft_reset_health(data, Graph, 2);
	ft_reset_health(data, Graph, 3);
}

void	ft_reset_health(t_data *data, t_sdl *Graph, int player)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	int j;
	int i;
	int dist;

	dist = (Graph->player_nbr->w * 20 - Graph->heart_pos->w * 4) / 3 + Graph->heart_pos->w;
	i = 0;
	while (i < 4)
	{
		heart = (SDL_Rect){Graph->heart_pos->x + dist * i++, Graph->heart_pos->y + (Graph->info_marc->h) * player, Graph->heart[0]->w, Graph->heart[0]->h};
		SDL_LockTexture(Graph->info_text, &heart, (void **)&pixel, &pitch);
		SDL_LockSurface(Graph->heart[0]);
		j = 0;
		while (++j < Graph->heart[0]->h)
			memcpy(pixel + j * pitch, Graph->heart[0]->pixels + j * Graph->heart[0]->pitch, Graph->heart[0]->pitch);
		SDL_UnlockSurface(Graph->heart[0]);
		SDL_UnlockTexture(Graph->info_text);
	}
}

void	ft_check_health(t_data *data, t_sdl *Graph, int player, int cicle_pre_die)
{
	int pitch;
	char *pixel;
	SDL_Rect heart;
	static unsigned int top[4] = {0, 0, 0, 0};
	int j;
	int i;
	int pos;
	int dist;

//	if ((cicle_pre_die * 6 / data->cycle_to_die) != pos || !pos)
//	{
	i = 0;
	if (!top[player])
		top[player] = data->cycle_to_die;
	dist = (Graph->player_nbr->w * 20 - Graph->heart_pos->w * 4) / 3 + Graph->heart_pos->w;
	if (data->players[player].live_counter)
	{
		top[player] = data->cycle_to_die;
		ft_reset_health(data, Graph, player);
		return ;
	}
	while (cicle_pre_die <= top[player] && i < 4)
	{
		pos = cicle_pre_die * 7 * 4 / top[player];
		if ((pos + 1) > i * 7 && (pos + 1) <= (i + 1) * 7)
		{
			pos -= i * 7;
			heart = (SDL_Rect){Graph->heart_pos->x + dist * i, Graph->heart_pos->y + (Graph->info_marc->h) * player, Graph->heart[pos]->w, Graph->heart[pos]->h};
			SDL_LockTexture(Graph->info_text, &heart, (void **)&pixel, &pitch);
			SDL_LockSurface(Graph->heart[pos]);
			j = 0;
			while (++j < Graph->heart[pos]->h)
				memcpy(pixel + j * pitch, Graph->heart[pos]->pixels + j * Graph->heart[pos]->pitch, Graph->heart[pos]->pitch);
			SDL_UnlockSurface(Graph->heart[pos]);
			SDL_UnlockTexture(Graph->info_text);
		}
		i++;
	}
//	}
}