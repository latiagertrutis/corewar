/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_alloc_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:35:20 by jagarcia          #+#    #+#             */
/*   Updated: 2018/07/29 17:38:00 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char *read_alloc_size(int fd, int size)
{
	char *rtn;

	rtn = (char *)malloc(sizeof(char) * size);
	read(fd, rtn, size);
	return (rtn);
}
