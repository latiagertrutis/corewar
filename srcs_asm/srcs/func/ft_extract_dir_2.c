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

static int	ft_extract_dir_label(t_line **line, int i, int n_line, int pos)
{
	char	*l;
	int	cnt;

	cnt = 0;
	l = line[0]->line;
	line[0]->arg_lab[pos] = &l[i];
	while (l[++i] && (l[i] != ' ' && l[i] != '\t' && l[i] != SEPARATOR_CHAR && l[i] != COMMENT_CHAR))
		cnt += l[i];
	line[0]->arg[pos] = cnt % (HASH_SIZE - 1);
	return (i);
}

static int	ft_set_ocp(int pos, int ocp)
{
	if (pos == 0)
		ocp = ocp | 0b10000000;
	else if (pos == 1)
		ocp = ocp | 0b00100000;
	else
		ocp = ocp | 0b00001000;
	return (ocp);
}

int	ft_extract_dir_2(t_line **line, int i, int n_line, int pos)
{
	line[0]->arg_size[pos] = IND_SIZE;
	line[0]->ocp = ft_set_ocp(pos, line[0]->ocp);
	if (line[0]->line[i] == LABEL_CHAR)
		i = ft_extract_dir_label(line, i, n_line, pos);
	else
		i = ft_atoi_asm(line[0]->line, i, &line[0]->arg[pos]);
	if ((i = ft_jmp_to_next(line[0]->line, i)) == -1)
		ft_error_par(n_line, 0, "direct", "%142,");
	line[0]->w += IND_SIZE;
	return (i);
}
