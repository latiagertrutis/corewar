/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/09 01:33:48 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> //printf !!

static void print_board(char *board)
{
int i;

	i = 0;
	while(i < MEM_SIZE)
	{
		if (board[i] < 16)
			ft_putchar('0');
		ft_putstr(ft_ltoa_base((int)board[i], 16));
		if ((i+1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
	}
}

int main(int ac, char **av)
{
	t_data		data;

	data = (t_data){ac - 1, NULL, NULL};
	if (!init_corewar(&data))
		ft_error("malloc failed");
	take_champions(&data, av);
	put_champs_to_arena(&data);
	print_memory((void *)(data.arena->board), MEM_SIZE, 64, 1);
	return (0);
}
