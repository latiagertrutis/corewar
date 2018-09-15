#include "libasm.h"

//cambiar cast

int		ft_extract_label_line(t_line *line, t_label *label, int pos)
{
	t_label *tmp;

//	ft_putstr(line->arg_lab[pos]);
//	write(1, "\n", 1);
//	ft_putstr(label->name);
//	write(1, "\n", 1);
	tmp = NULL;
	if (ft_strcmp_to(label->name, line->arg_lab[pos]))
	{
		return (label->pos - line->pos);
	}
	else if (label->copy != NULL)
		tmp = label->copy;
	while (tmp)
	{
		if (ft_strcmp_to(tmp->name, line->arg_lab[pos]))
			return (tmp->pos - line->pos);
		tmp = tmp->copy;
	}
	ft_error_label(0, 1, line->arg_lab[pos]);
	return (0);
}
