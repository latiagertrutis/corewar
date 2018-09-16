#include "libasm.h"

static t_line *label_to_line(t_line *line, t_label **label, int fd)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (line->arg_lab[i])
				line->arg[i] = ft_extract_label_line(line, label[line->arg[i]], i);
		if (line->arg_size[i])
		{
			ft_invert_bytes(&line->arg[i], line->arg_size[i]);
			write(fd, &line->arg[i], line->arg_size[i]);
		}
	}
	return (line);
}

void ft_line_to_file(t_line *bgn, t_label ** label, int fd)
{
	t_line *line;

	line = bgn->next;
	while (line)
	{
		if (line->order_n)
		{
			write(fd, &(line->order_n), 1);
			if (line->ocp != 1)
				write(fd, &(line->ocp), 1);
			line = label_to_line(line, label, fd);
		}
		line = line->next;
	}
}
