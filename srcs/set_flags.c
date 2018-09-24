/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:46:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/23 15:22:33 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		set_flags(const int ac, const char **av, unsigned int *flags, t_flag_value *f_value)
{
	unsigned char i;

	i = 0;
	if (av[0][0] == '-' && av[0][1] == 'i' && av[0][2] == '\0')
		*flags |= 0x1;
	else
		ft_error("invalid flag.\n");
	return (1);
}
