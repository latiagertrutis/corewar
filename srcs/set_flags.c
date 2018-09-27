/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:46:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/27 19:33:22 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

int		set_flags(const int ac, const char **av, unsigned int *flags, t_flag_value *f_value)
{
	unsigned char i;

	i = 1;
	while (av[0][i])
	{
		if (av[0][i] == 'v')//visualicer
			*flags |= 0x1;
		else if (av[0][i] == 'f')//fullscreen
			*flags |= 0x2;
		else if (av[0][i] == 'i')//instructions
			*flags |= 0x4;
		else if (av[0][i] == 'd')//deaths
			*flags |= 0x8;
		else
			ft_error("invalid flag.\n");
		i++;
	}
	return (1);
}
