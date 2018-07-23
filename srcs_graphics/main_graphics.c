/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:27:54 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/13 05:30:10 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/corewar.h"

static void ini_board(t_sdl *Game)
{
	SDL_Surface *surf;
	SDL_Rect border[4];
	SDL_Texture *tex_border;

	if (!(surf = SDL_GetWindowSurface(Game->screen.window)))
	{
		printf("SDL_GetWindowSurface: %s\n", SDL_GetError());
		exit(1);
	}
	border[0] = (SDL_Rect){Game->screen.w - (Game->screen.w * LEFT_BORDER), 0, LEFT_BORDER * Game->screen.w, Game->screen.h};
	border[1] = (SDL_Rect){0, 0, Game->screen.w, Game->screen.h * UPPER_BORDER};
	border[2] = (SDL_Rect){0, Game->screen.h - floor((Game->screen.h * BOTTOM_BORDER)), Game->screen.w, Game->screen.h * BOTTOM_BORDER};
	border[3] = (SDL_Rect){0, 0, Game->screen.w * RIGHT_BORDER, Game->screen.h};
	SDL_FillRects(surf, border, 4, SDL_MapRGB(surf->format, 52, 52, 52));
	if (!(tex_border = SDL_CreateTextureFromSurface(Game->screen.Renderer, surf)))
	{
		printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
		exit(1);		
	}
	SDL_RenderCopy(Game->screen.Renderer, tex_border, NULL, NULL);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex_border);
}

static SDL_Surface	*write_byte(int byte, int x, int y, TTF_Font *font)
{
	SDL_Surface *surf_byte;
	char		*hexa_byte;
	SDL_Color	color;
	char		*str;

	color = (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE};
	hexa_byte = ft_itoa_base(byte, 16);
	if (strlen(hexa_byte) == 1)
	{
		str = strdup("00\0");
		str[1] = *hexa_byte;
		free(hexa_byte);
		hexa_byte = str;
	}
	printf("byte = %s\n", hexa_byte);
	surf_byte = TTF_RenderUTF8_Blended(font, hexa_byte, color);
	return (surf_byte);
}

static void print_board(t_sdl *Game, char board[4 * 1024])
{
	SDL_Surface *map;
	SDL_Rect	byte;
	SDL_Surface *tmp;
	int			i[2];
	TTF_Font	*font;
	int			font_dim[2];
	SDL_Texture *tex_map;

	map = SDL_CreateRGBSurface(0, Game->screen.w - (Game->screen.w * RIGHT_BORDER) - (Game->screen.w * LEFT_BORDER), Game->screen.h - (Game->screen.h * UPPER_BORDER) - (Game->screen.h * BOTTOM_BORDER), 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	font = TTF_OpenFont("./Ubuntu-B.ttf", 18);
	if (!map)
	{
		printf("SDL_CreateRGBSurface: %s\n", SDL_GetError());
		exit(1);
	}
	TTF_SizeText(font, "A", font_dim, font_dim + 1);
	i[0] = 0;
	while (i[0] < 64)
	{
		i[1] = 0;
		while (i[1] < 64)
		{
			tmp = write_byte(board[i[0] * i[1]], map->w / 64, map->h / 64, font);
			byte = (SDL_Rect){i[0] * font_dim[0] * 2, i[1] * font_dim[1], tmp->w, tmp->h};
			SDL_BlitSurface(tmp, NULL, map, &byte);
			SDL_FreeSurface(tmp);
			i[1]++;
		}
		i[0]++;
	}
	tex_map = SDL_CreateTextureFromSurface(Game->screen.Renderer, map);
	SDL_RenderCopy(Game->screen.Renderer, tex_map, NULL, &(SDL_Rect){Game->screen.w * RIGHT_BORDER, Game->screen.h * UPPER_BORDER, map->w, map->h});
}
int	main_graphics()
{
	t_sdl Game;
	SDL_Event event;
	char	board[4 * 1024];

	Game = (t_sdl){ft_set_flags(argn, argv), SDL_FALSE, {SCREEN_SCALE * SCREEN_W, SCREEN_SCALE * SCREEN_H, SCREEN_NAME, NULL, NULL}, {NULL}};
	ft_ini_graphics(&Game);
	SDL_RenderClear(Game.screen.Renderer);
	ini_board(&Game);
	print_board(&Game, board);
	SDL_RenderPresent(Game.screen.Renderer);
	while (Game.running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				Game.running = SDL_FALSE;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					Game.running = SDL_FALSE;
			}
		}
	}
	ft_quit_graphics(&Game);
	return (0);
}
