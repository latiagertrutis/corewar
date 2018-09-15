#include "libasm.h"

void	ft_printlabel(t_label **label)
{
	t_label	*tmp;
	int i;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (label[i] != NULL)
		{
			ft_putnbr(label[i]->id);
			ft_putstr(" OK! ");
			ft_putchar('\t');
//			ft_putstr(label[i]->name);
			tmp = label[i];
			while (tmp->copy)
			{
				ft_putstr(" -> ");
				ft_putnbr(tmp->copy->id);
//				ft_putchar('\t');
//				ft_putstr(tmp->copy->name);
				tmp = tmp->copy;
			}
		}
		else
			ft_putnbr(i);
			ft_putchar('\n');
	}
}
