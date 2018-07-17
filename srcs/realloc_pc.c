/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_pc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:37:40 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/17 12:37:42 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_pc	*realloc_pc(t_player *player, t_pc *pc, const unsigned int nb_pc)
{
	t_pc *new_pc;

	if (!(new_pc = (t_pc *)malloc(sizeof(t_pc) * (nb_pc + 20))))
		ft_error("malloc failed");
	ft_memcpy(new_pc, pc, sizeof(t_pc) * nb_pc);
	free(pc);
	return (new_pc);
}
