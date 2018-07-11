/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:48:34 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/10 01:32:32 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> //printf !!

int main(int ac, char **av)
{
	t_data		data;

	if (ac < 2 || ac > 5)
		put_usage();
	data = (t_data){ac - 1, NULL, NULL, {"\033[0m", "\033[38;5;1m", "\033[38;5;2m",
							"\033[38;5;3m", "\033[38;5;4m"}};
	if (!init_corewar(&data))
		ft_error("malloc failed");
	take_champions(&data, av);
	
	put_champs_to_arena(&data);
	// print_board(&data, data.arena->board);
//	print_memory((void *)(data.arena->board), MEM_SIZE, 64, 1);

	
	exe_players(&data);

	
	free(data.arena);
	free_players(data.players, data.n_players);
	return (0);
}

//4 Empezar con las intrucciones: Mateo pares, Mikel impares
