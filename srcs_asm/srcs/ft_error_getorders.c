/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_getorders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:42:52 by jpinyot           #+#    #+#             */
/*   Updated: 2018/10/05 17:42:54 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	invalid_token(int l)
{
	ft_puterr("\x1B[91mInvalid token at line ");
	ft_putnerr(l);
	ft_puterr("\n\e[0m");
}

void		ft_error_getorders(int l, int sel)
{
	l++;
	if (sel == 0)
		invalid_token(l);
	exit(-1);
}
