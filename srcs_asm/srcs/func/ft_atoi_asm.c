#include "libasm.h"

MAX_CAST		ft_atoi_asm(const char *str, int pos, int *val)
{
	MAX_CAST	n;
	size_t	i;
	size_t	neg;

	n = 0;
	i = pos - 1;
	neg = 0;
	if (str[pos] == 45 || str[pos] == 43)
	{
		if (str[pos] == 45)
			neg++;
		i++;
	}
	while (str[++i] >= 48 && str[i] <= 57)
		n = (10 * n) + (str[i] - 48);
	if (neg > 0)
		n *= -1;
	*val = n;
	return (i);
}