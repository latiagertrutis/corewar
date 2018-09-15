#include "libasm.h"

static char	*ft_strtabspace(char *s, int j)
{
	int i;

	i = j;
	while (s[i] && (s[i] == '\t' || s[i] == ' '))
		i++;
	if (s[i] != '"')
		return (NULL);
	return (&s[i + 1]);
}

static t_header	ft_header_name(char *l, int n_l, int i, t_header h)
{
	char	*tmp;
	int		j;

	if (!(tmp = ft_strtabspace(l, i)))
		ft_error_getname(n_l, 1);
	if ((j = ft_strlen(tmp)) > (PROG_NAME_LENGTH + 1))
		ft_error_getname(n_l, 2);
	if (tmp[j - 1] != '"')
		ft_error_getname(n_l, 1);
	h.prog_name = tmp;
	h.name_size = j - 1;
	h.name_line = l;
	return (h);
}

static t_header	ft_header_comment(char *l, int n_l, int i, t_header h)
{
	char	*tmp;
	int		j;

	if (!(tmp = ft_strtabspace(l, i)))
		ft_error_getname(n_l, -1);
	if ((j = ft_strlen(tmp)) > (COMMENT_LENGTH + 1))
		ft_error_getname(n_l, -2);
	if (tmp[j - 1] != '"')
		ft_error_getname(n_l, -1);
	h.comment = tmp;
	h.comment_size = j - 1;
	h.comment_line = l;
	return (h);
}

t_header	ft_getname(char *line, int n_line, t_header h)
{
	char	*tmp;
	int	i;
	int 	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if ((i = ft_strcmp_index(&line[j], NAME_CMD_STRING)) != -1)
		h = ft_header_name(line, n_line, i + j, h);
	else if ((i = ft_strcmp_index(&line[j], COMMENT_CMD_STRING)) != -1)
		h = ft_header_comment(line, n_line, i + j, h);
	else if (line[j] != COMMENT_CHAR)
		ft_error_getname(n_line, 0);
	return (h);
}
