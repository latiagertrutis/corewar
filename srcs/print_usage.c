/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 21:56:33 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/10/06 14:15:24 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_corewar.h"

void	print_usage(void)
{
	ft_putstr("Usage: ./corewar [-n N -dump N | -i -v -f -k][foo_1.cor ... foo_\
n.cor]\n\
-n N		Enter the number of the next player\n\
======> INFORMATION FLAGS <==================================================\n\
-i		Shows the operations.\n-k		Shows the deaths.\n-dump		Dumps m\
emory in stdout.\n\
======> SDL FLAGS <==========================================================\n\
-v		Visual mode.\n-f		Fullscreen mode.\n\
| (• ◡•)| (❍ᴥ❍ʋ)(ノಠ益ಠ)ノ彡┻━┻¯\\_(ツ)_/¯༼ つ ◕_◕ ༽つರ_ರ(°,,°)┬─┬ノ( º _ ºノ)\
ಠoಠ\n");
}
