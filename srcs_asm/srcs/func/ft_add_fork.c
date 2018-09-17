/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:47:32 by jpinyot           #+#    #+#             */
/*   Updated: 2018/09/17 12:47:33 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	intern_error(int l, int sel)
{
	ft_putstr("\x1B[91mInvalid fork parameters at line ");
	ft_putnbr(l);
	if (sel == 0)
		ft_putstr(":\n\t\x1B[97m-At first parameter.");
	ft_putstr("\n\t\x1B[92mUsage:\x1B[97m");
	ft_putstr("\n\t-The first parameter must be direct.");
	ft_putstr("\n\t\x1B[92mExample:\x1B[97m\n\t");
	ft_putstr("fork\t%12");
	exit(-1);
}

t_line		*ft_add_fork(char *l, int cnt, int j, int n_line)
{
	t_line	*line;
	int		i;

	if ((i = ft_strcmp_index_jmp(&l[j], "fork")) == -1 || l[i] == 0)
		ft_error_order(n_line, 0, "fork", "fork\t%432");
	i += j;
	line = ft_newline(NULL, 12, l, 1);
	if (l[i] == DIRECT_CHAR)
		i = ft_extract_dir_2(&line, i + 1, n_line, 0);
	else
		intern_error(n_line, 0);
	ft_check_for_coments(l, i, n_line);
	line->ocp = 1;
	return (line);
}
