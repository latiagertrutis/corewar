/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:46:04 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/10/06 13:07:00 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

static unsigned char	take_player_nb(const char *str, t_flag_value *f_value)
{
	int32_t				num;

	num = 0;
	if (ft_issdigit((char *)str))
		num = ft_atoi(str);
	else
		ft_error("Error: number player is not only numbers\n");
	if (g_n_players < MAX_PLAYERS)
		f_value->player_nb[g_n_players] = num;
	return (2);
}

static unsigned char	take_dump_nb(const char *str, t_flag_value *f_value)
{
	int32_t				num;

	num = 0;
	if (ft_issdigit((char *)str))
		num = ft_atoi(str);
	else
		ft_error("Error: number dump is not only numbers\n");
	f_value->dump_cycle = num;
	return (2);
}

int						set_flags(const int ac, const char **av, unsigned int *flags, t_flag_value *f_value)
{
	unsigned char i;
	unsigned char ret;

	i = 1;
	ret = 1;
	if (ac > 1 && !ft_strcmp("-dump", av[0]))
	{
		*flags |= 0x10;
		return (take_dump_nb(av[1], f_value));
	}
	while (av[0][i])
	{
		if (av[0][i] == 'v')//visualicer
			*flags |= 0x1;
		else if (av[0][i] == 'f')//fullscreen
			*flags |= 0x2;
		else if (av[0][i] == 'i')//instructions
			*flags |= 0x4;
		else if (av[0][i] == 'k')//deaths
			*flags |= 0x8;
		else if (ac > 1 && av[0][i] == 'n')//number
			ret = take_player_nb(av[1], f_value);
		else
			ft_error("Error: invalid flag.\n");
		i++;
	}
	return (ret);
}
