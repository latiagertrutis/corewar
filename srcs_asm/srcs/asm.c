/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:41:06 by jpinyot           #+#    #+#             */
/*   Updated: 2018/09/30 23:07:38 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static t_header	name_and_comment(int fd)
{
	int			j;
	int			i;
	char		*line;
	t_header	h;

	j = 1;
	i = 0;
	h.prog_name = NULL;
	h.comment = NULL;
	while ((i = get_next_line(fd, &line) > 0) > 0)
	{
		if (line[0] != 0)
			h = ft_getname(line, j, h);
		else
			ft_strdel(&line);
		if (h.prog_name && h.comment)
			break ;
		j++;
	}
	if (i < 1)
		ft_error_getname(j, 0);
	h.line_n = j;
	return (h);
}

static t_line	*ft_getpos(t_line *line)
{
	line->next->pos = line->pos + line->w;
	if (line->next->label)
		line->next->label->pos = line->next->pos;
	return (line->next);
}

static t_line	*orders(int fd, int line_n, t_label **label)
{
	int			j;
	char		*l;
	t_line		*line;
	t_line		*bgn;

	line = ft_newline(NULL, -1, NULL, 0);
	bgn = line;
	while ((get_next_line(fd, &l) > 0) > 0)
	{
		j = 0;
		while (l[j] && (l[j] == ' ' || l[j] == '\t'))
			j++;
		if (l[j] != 0 && l[j] != COMMENT_CHAR && l[j] != END_LINE_CHAR)
		{
			line->next = ft_getorders(l, label, j, line_n);
			line = ft_getpos(line);
		}
		else
			ft_strdel(&l);
		line_n++;
	}
	bgn->w = line->w + line->pos;
	return (bgn);
}

int				assembler(int fd, char *filename, int sel)
{
	t_header	header;
	t_line		*line;
	t_label		*label[HASH_SIZE];
	int			i;
	int			fd2;

	i = -1;
	while (++i < HASH_SIZE)
		label[i] = NULL;
	header = name_and_comment(fd);
	line = orders(fd, header.line_n, label);
	if (sel == 1)
	{
		if ((fd2 = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			exit(-1);
		ft_header_to_file(header, fd2, line->w);
		ft_line_to_file(line, label, fd2);
		close(fd2);
	}
	else
		ft_print_asm(header, line, label, line->w);
	return (0);
}
