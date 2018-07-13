/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_SDL_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 05:14:24 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/13 05:19:15 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_SDL_error(char *str, int mode)
{
	char *tmp;

	tmp = ft_strjoin(str, ": %s\n");
	if (mode)
		ft_printf(tmp, SDL_GetError());
	else
		ft_printf(tmp, TTF_GetError());
	free(tmp);
	exit(1);
}
