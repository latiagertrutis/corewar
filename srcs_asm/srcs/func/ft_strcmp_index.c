#include "libasm.h"

int	ft_strcmp_index(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	if (s2[i] == 0 && i > 0)
		return (i);
	return (-1);
}

int	ft_strcmp_index_jmp(char *s1, char *s2)
{
	int i;
	int j;

	i = -1;
	while (s1[++i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	if (s2[i] == 0 && i > 0)
	{
		while (s1[i] == ' ' || s1[i] == '\t')
			i++;
		return (i);
	}
	return (-1);
}
