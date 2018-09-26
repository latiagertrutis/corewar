/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:46:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/09/26 15:52:17 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

int		set_flags(const int ac, const char **av, unsigned int *flags, t_flag_value *f_value)
{
	unsigned char i;

	i = 0;
	if (av[0][0] == '-' && av[0][1] == 'i' && av[0][2] == '\0')
		*flags |= 0x1;
	else if (av[0][0] == '-' && av[0][1] == 'f' && av[0][2] == '\0')
		*flags |= 0x2;
	else
		ft_error("invalid flag.\n");
	return (1);
}
