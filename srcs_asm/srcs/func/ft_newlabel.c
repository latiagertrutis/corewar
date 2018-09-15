#include "libasm.h"

t_label		*ft_newlabel(char *name, int id)
{
	t_label *lab;

	if (!(lab = (t_label *)malloc(sizeof(t_label))))
		exit (-1);
	if (name)
		lab->name = name;
	else
		lab->name = NULL;
	lab->id = id;
	lab->pos = -1;
	lab->copy = NULL;
	lab->next = NULL;
	return (lab);
}
