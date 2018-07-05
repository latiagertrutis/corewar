/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabalza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 19:02:21 by mzabalza          #+#    #+#             */
/*   Updated: 2018/07/01 19:02:24 by mzabalza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>


char	*get_content(int fd)
{
	// char buff[1];
	char *content;

	if (!(content = (char *)malloc(sizeof(char) * (HEADER_SIZE))))
		exit(1);
	read(fd, content, HEADER_SIZE);
	
	int i = 0;
	while (i < HEADER_SIZE)
		printf("%02X ", (unsigned char)content[i++]);
	return (content);
}
