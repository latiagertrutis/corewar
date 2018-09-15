#include "libasm.h"

/* https://linux.die.net/man/3/open */
/* open macros */

static t_header	name_and_comment(int fd)
{
	int		i;
	int		j;
	char		*line;
	t_header	h;

	i = 0;
	j = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 0)
			i--;
		else
			h = ft_getname(line, j, h);
		if (++i == 2)
			break ;

		j++;
	}
	h.line_n = j;
	return (h);
}

static void	print_line(t_line *l)
{
	ft_putstr(l->line);
	ft_printf(" -->%i--%i<--\n%i\t%i\t%i\n%i\t%i\t%i\n", l->order_n, l->ocp, l->arg[0], l->arg[1], l->arg[2], l->arg_size[0], l->arg_size[1], l->arg_size[2]);
	ft_printf("-->pos=%i\t-->w=%i\n\n",l->pos, l->w);
}

static t_line	*ft_getpos(t_line *line)
{
	line->next->pos = line->pos + line->w;
	if (line->next->label)
		line->next->label->pos = line->next->pos + line->next->w;
	return (line->next);
}

static t_line	*orders(int fd, int line_n, t_label **label)
{
	int		j;
	char		*l;
	t_line		*line;
	t_line		*bgn;
	
	line = ft_newline(NULL, -1, NULL, 0);
	bgn = line;
	while (get_next_line(fd, &l) > 0)
	{
		j = 0;
		while (l[j] && (l[j] == ' ' || l[j] == '\t'))
			j++;
		if (l[j] != 0 && l[j] != COMMENT_CHAR)
		{
			line->next = ft_getorders(l, label, j, line_n);
			line = ft_getpos(line);
			print_line(line);	//print
		}
		line_n++;
	}
//	ft_printlabel(label);
	return (bgn);
}

int	assembler(int fd, char *filename)
{
	t_header	header;
	t_line		*line;
	t_label 	*label[HASH_SIZE];
	int i;
	int fd2;

	i = -1;
	while (++i < HASH_SIZE)
		label[i] = NULL;
	header = name_and_comment(fd);
	line = orders(fd, header.line_n, label);
	if ((fd2 = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		exit (-1);
	char a = 0xea;
//	write(fd2, "hola mateo", 15);
	write(fd2, &a, 1);
	return (0);
}
