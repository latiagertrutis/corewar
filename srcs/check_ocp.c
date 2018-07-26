/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ocp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:13:40 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/26 16:05:05 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char		check_ocp(const unsigned char ocp)
{
	return ((0xC & ocp) && (0x30 & ocp) && (0xC0 & ocp));
}
