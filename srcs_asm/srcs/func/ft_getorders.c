#include "libasm.h"

static t_line	*get_line(char *l, t_label **label, int i, int n_line)
{
	int	cnt;
	int	j;
	t_line *line;

	cnt = 0;
	i = ft_jmp_s_t(l, i);
	j = i - 1;
	while (l[++j] && l[j] != LABEL_CHAR && l[j] != DIRECT_CHAR && l[j] != ' ' && l[j] != '\t')
		cnt += l[j];
	if (l[j] == DIRECT_CHAR || l[j] == ' ' || l[j] == '\t')
	{
		line = ft_add_new_line(l, cnt, i, n_line);
		line->label = label[HASH_SIZE -1 ];
	}
	else if (l[j] == 0)
		line = ft_newline(label[HASH_SIZE - 1], 0, l, 0);
	else
		ft_error_getorders(n_line, 0);
	label[HASH_SIZE - 1] = NULL;
	return (line);
}

t_line		*ft_getorders(char *l, t_label **label, int i, int n_line)
{
	t_line	*line;
	int	cnt;
	int	j;

	cnt = 0;
	j = i - 1;
	if (l[i] == '.')
		ft_error_getorders(n_line, 0);
	while (l[++j] && l[j] != LABEL_CHAR && l[j] != DIRECT_CHAR && l[j] != ' ' && l[j] != '\t')
		cnt += l[j];
	if (l[j] && l[j] == LABEL_CHAR)
	{
		label = ft_add_new_label(label, cnt, l, i);
		line = get_line(l, label, j + 1, n_line);
	}
	else if (l[j] && (l[j] == DIRECT_CHAR || l[j] == ' ' || l[j] == '\t'))
		line = ft_add_new_line(l, cnt, i, n_line);
	else
		ft_error_getorders(n_line, 0);
	return (line);
}
