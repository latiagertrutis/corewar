/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pc_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 17:08:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/08/07 17:30:55 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		clean_pc_arr(t_pc *pc, const unsigned int nb_pc)
{
	size_t i;
	size_t actv;

	i = 0;
	actv = 0;
	while (i < nb_pc)
	{
		if (!pc[i].active)
		{
			if (!actv)
				actv = i + 1;
			while (actv < nb_pc && !pc[actv].active)
				actv++;
			if (actv < nb_pc)
			{
				pc[i] = pc[actv];
				pc[actv].active = 0;
				actv++;
			}
			else
				return ;
		}
		i++;
	}
}
