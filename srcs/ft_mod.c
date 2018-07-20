/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:01:05 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/19 15:52:33 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	ft_mod(const int nb, const unsigned int mod)
{
	int aux;

	if (nb >= 0)
		return (nb % mod);
	if ((aux = mod + nb) < 0)
		aux = ft_mod(aux, mod);
	return (aux);
}
