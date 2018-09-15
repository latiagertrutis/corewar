#include "libasm.h"

static void ft_putstr_dot(char *s)
{
	int i;

	i = -1;
	while (s[++i] && s[i] != ':' && s[i] != ' ' && s[i] != 't')
		write (1, &s[i], 1);
}

static void	label_copy(int l, char *s, char *ex)
{
	ft_putstr("\x1B[91mInvalid label identifier:");
	ft_putstr(":\n\t\x1B[92mUsage:\x1B[97m");
	ft_putstr("\n\t-Each label identifier must be unique.");
	ft_putstr("\n\t-Identifier \"");
	ft_putstr_dot(ex);
	ft_putstr("\" is repeated.");
}

void ft_error_label(int l, int sel, char *s)
{
	l++;
	if (sel == 0)
		label_copy(l, s, s);
	exit(-1);
}
