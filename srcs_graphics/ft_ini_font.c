/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 11:09:42 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/19 14:42:37 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_ini_font(t_sdl *Graph)
{
	int	font_size;

	font_size = 1;
	ft_printf("square mide %i x %i\n", Graph->square->w, Graph->square->h);
	while (Graph->font_info.w + 5 < Graph->square->w && Graph->font_info.h + 5
			< Graph->square->h)
	{
		if (Graph->font_info.font)
			TTF_CloseFont(Graph->font_info.font);
		if (!(Graph->font_info.font = TTF_OpenFont("./Ubuntu-B.ttf", font_size++)))
			ft_SDL_error("TTF_OpenFont", MODE_TTF);
		TTF_SizeUTF8(Graph->font_info.font, "FF", &Graph->font_info.w,
				&Graph->font_info.h);
	}
}
