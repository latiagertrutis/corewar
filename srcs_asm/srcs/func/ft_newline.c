#include "libasm.h"

static t_line	*ft_nullarg(t_line *f)
{
	f->arg_lab[0] = NULL;
	f->arg_lab[1] = NULL;
	f->arg_lab[2] = NULL;
	f->arg_size[0] = 0;
	f->arg_size[1] = 0;
	f->arg_size[2] = 0;
	f->ocp = 0;
	f->pos = 0;
	return (f);
}

t_line		*ft_newline(t_label *l, int ord_n, char *line, int w)
{
	t_line	*file;

	if (!(file = (t_line *)malloc(sizeof(t_line))))
		exit (-1);
	if (l)
		file->label = l;
	else
		file->label = NULL;
	if (line)
		file->line = line;
	else
		file->line = NULL;
	file->order_n = ord_n;
	file->w = w;
	file = ft_nullarg(file);
	return (file);
}
