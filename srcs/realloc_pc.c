/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_pc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:37:40 by mzabalza          #+#    #+#             */
/*   Updated: 2018/08/02 23:49:13 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		clean_pc_arr(t_pc *pc, const unsigned int nb_pc)
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
			while (!pc[actv].active && actv < nb_pc)
				actv++;
			if (actv < nb_pc)
			{
				pc[i] = pc[actv];
//				pc[actv].active = 0;
				actv++;
			}
			else
				return (1);
		}
		i++;
	}
	if (actv)
		return (1);
	return (0);
}

t_pc	*realloc_pc(t_pc *pc, const unsigned int nb_pc)
{
	t_pc *new_pc;

	if (pc && clean_pc_arr(pc, nb_pc))
		return(pc);
	if (!(new_pc = (t_pc *)malloc(sizeof(t_pc) * (nb_pc + 20))))
		ft_error("malloc failed");
	//habria que inicializar todo a zero mejor no?
	//new_pc[0] = {0};
	//mejor eso o ft_memset()
	ft_memcpy(new_pc, pc, sizeof(t_pc) * nb_pc);
	free(pc);
	return (new_pc);
}
