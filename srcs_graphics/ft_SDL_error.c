/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_SDL_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:14:24 by jagarcia          #+#    #+#             */
/*   Updated: 2018/08/13 08:56:33 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_SDL_error(char *str, int mode)
{
	char *tmp;

	tmp = ft_strjoin(str, ": %s\n");
	if (mode > 0)
		ft_printf(tmp, SDL_GetError());
	else if (!mode)
		ft_printf(tmp, TTF_GetError());
	else
		ft_printf(tmp, IMG_GetError());
	free(tmp);
	exit(1);
}
