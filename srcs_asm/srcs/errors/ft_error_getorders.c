#include "libasm.h"

static void invalid_token(int l)
{
	ft_putstr("\x1B[91mInvalid token at line ");
	ft_putnbr(l);
}

void ft_error_getorders(int l, int sel)
{
	l++;
	if (sel == 0)
		invalid_token(l);
	exit(-1);
}
