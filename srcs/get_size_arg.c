/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:03:16 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/28 16:42:06 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	get_size_arg(const unsigned char ocp, const unsigned char n_arg, const unsigned int dir_size)
{
	unsigned char type;

	type = (ocp & (0xC0 >> (2 * n_arg))) >> (2 * (3 - n_arg));
	if (type == REG_CODE)
		return (1);
	if (type == DIR_CODE)
		return (dir_size ? 4 : 2);
	if (type == IND_CODE)
		return (2);
	else
		return (0);
}
