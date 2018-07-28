/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:05:59 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/28 21:53:08 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			exe_pc(t_pc *pc, t_arena *arena, t_data *data)
{
	unsigned char op_nb;

	op_nb = (arena->board[pc->pc % MEM_SIZE].mem) - 1;
	if (pc->wait_cycles > 1)
	{
		pc->wait_cycles--;
		return ;
	}
	else if (pc->wait_cycles == 1)
	{
		pc->wait_cycles--;
//		ft_printf("executing.. %d\n", op_nb);
		if (op_nb <= 15)
		{
			// data->func[op_nb](player, pc, arena, data);
			data->func[op_nb](pc, arena, data);
		}
	}
	else
	{
		if (op_nb <= 15)
			pc->wait_cycles = (data->op[op_nb].mana) - 1;
		else
			pc->pc = (pc->pc + 1) % MEM_SIZE;
	}
}



void 				exe_players(t_data *data)
{
	unsigned int k;
	unsigned int t;
	SDL_Event	event;

	data->i = 0;
	
	fill_r1(data);
//	print_board(data, data->arena->board);
	while(data->cycle_to_die > 0 && data->mods->running)
	{
		// write(1, "\x1b[H\x1b[2J", 7);
		// ft_putnbr(data->cycle_to_die);
		if (data->cycle_to_die <= 0)
			data->mods->running = 0;
		t = 0;
		while (t < data->cycle_to_die && data->mods->running)
		{

			// if (data->cycle_to_die <= 0)
			// 	break;
			// usleep(10);
			while (SDL_PollEvent(&event) && data->mods->visual)
			{
				if (event.type == SDL_QUIT)
					data->mods->running = 0;
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
						data->mods->running = SDL_FALSE;
					else if (event.key.keysym.sym == SDLK_SPACE)
						data->mods->pause = data->mods->pause ? 0 : 1;
					else if (event.key.keysym.sym == SDLK_RIGHT)
						data->mods->step = 1;
				}
				else if (event.type == SDL_KEYUP)
					if (event.key.keysym.sym == SDLK_RIGHT)
						data->mods->step = 0;
			}
			// usleep(100);
			if (!data->mods->pause || data->mods->step)
			{
//				j = 0;
//				while(j < data->n_players)
//				{

				k = data->nb_pc;
				ft_printf("EXE_INI\n");
				while (k)
				{
					ft_printf("pc live: %u\npc active: %u\ncycle to die: %d\n", data->pc[k - 1].live, data->pc[k - 1].active, data->nb_cycles);
					// exe_pc((data->players) + j, (data->players[j].pc) + k - 1, data->arena, data);
					if (data->pc[k - 1].active)
					{
						if (data->nb_cycles != 0 && !(data->nb_cycles % CYCLE_TO_DIE))
						{
							if (!(data->pc[k - 1].live))
							{
								data->pc[k - 1].active = 0x0;
								k--;
								continue;
							}
							else
								data->pc[k - 1].live = 0x0;
						}
						exe_pc((data->pc) + k - 1, data->arena, data);
					}
					k--;
				}
				ft_printf("EXE_FIN\n");
//					j++;
//				}
				t++;
				data->nb_cycles++;

				if (data->mods->visual)
				{
					ft_board_to_screen(data->arena->Graph, data->arena->board, data);
					ft_set_back_to_front(data->arena->Graph, data);
				}
				// if (data->nb_cycles == 100)
				// 	exit(1);
			}
		}
		check_live_count(data->players, data->n_players, data);
	}
	check_winner(data->players, data->n_players);
}
