/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/06/27 20:24:58 by mzabalza         ###   ########.fr       */
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
		ft_putstr(ft_itoa_base((int)board[i], 16));
		if ((i+1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
	}
}

int main(int ac, char **av)
{
	t_arena		*arena;
	t_player	*players;
	
	if (!init_corewar(&arena, &players, ac))
		ft_error("malloc failed");
	// print_board(arena->board);
	take_champions(ac, av, players);


	

	//preguntar mateo operdores binarios

	return (0);
}
