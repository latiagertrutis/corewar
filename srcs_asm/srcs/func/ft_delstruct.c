#include "libasm.h"

static void	ft_linedel(t_line *line)
{
	if (line->line)
		ft_strdel(&line->line);
	free(line);
}

static void	ft_labeldel(t_label *label)
{
	t_label *tmp;
	t_label *tmp2;

	if (label->copy)
	{
		tmp = label->copy;
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->copy;
			free(tmp2);
		}
	}
	free(label);
}

void	ft_delstruct(t_label **label, t_line *line)
{
	t_line	*tmp;
	int		i;

	i = -1;
	while (line)
	{
		tmp = line;
		line = line->next;
		ft_linedel(tmp);
	}
	while (++i < HASH_SIZE)
	{
		if (label[i])
			ft_labeldel(label[i]);
	}
}
