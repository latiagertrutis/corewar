#include "libasm.h"

void	ft_check_for_coments(char *l, int i, int n_line)
{
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	if (l[i] != 0 && l[i] != COMMENT_CHAR)
		ft_error_order(n_line, 1, NULL, NULL);
}

int	ft_jmp_s_t(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

int	ft_hash_it(int id, int range)
{
//	ft_putnbr(id);
	id = id % range;
//	ft_printf("-->%i\t\tft_functions.c\n", id);
	return (id);
}
