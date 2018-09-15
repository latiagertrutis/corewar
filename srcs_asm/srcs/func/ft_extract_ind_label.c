#include "libasm.h"

static int	ft_jmp_to_next(char *l, int i)
{
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	if (l[i] != SEPARATOR_CHAR && l[i] != 0 && l[i] != COMMENT_CHAR)
		return (-1);
	if (l[i] == 0 || l[i] == COMMENT_CHAR)
		return (i);
	i++;
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	return (i);
}

static int	ft_extract_label(t_line **line, int i, int n_line, int pos)
{
	char	*l;
	int	cnt;

	cnt = 0;
	l = line[0]->line;
	line[0]->arg_lab[pos] = &l[i];
	while (l[++i] && (l[i] != ' ' && l[i] != '\t' && l[i] != SEPARATOR_CHAR))
		cnt += l[i];
	line[0]->arg[pos] = cnt;
	return (i);
}

static int	ft_set_ocp(int pos, int ocp)
{
	if (pos == 0)
		ocp = ocp | 0b11000000;
	else if (pos == 1)
		ocp = ocp | 0b00110000;
	else
		ocp = ocp | 0b00001100;
	return (ocp);
}

int	ft_extract_ind_label(t_line **line, int i, int n_line, int pos)
{
	line[0]->arg_size[pos] = IND_SIZE;
	line[0]->ocp = ft_set_ocp(pos, line[0]->ocp);
	i = ft_extract_label(line, i, n_line, pos);
	if ((i = ft_jmp_to_next(line[0]->line, i)) == -1)
		ft_error_par(n_line, 0, "indirect", ":ld3,");
	line[0]->w += IND_SIZE;
	return (i);
}
