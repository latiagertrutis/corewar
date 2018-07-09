#include "corewar.h"

#include <unistd.h>

void	print_memory(const void *addr, size_t size, int line, int space)
{
	size_t			i;
	int 			j;
	unsigned char	*p;
	char 			*hexa;

	hexa = "0123456789abcdef";
	p = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < line && i + j < size)
		{
			if (p[i + j])
				ft_printf("{green}");
			ft_putchar(hexa[*(p + i + j)/16]); //%16?
			ft_putchar(hexa[*(p + i + j) % 16]);
			if (space == 1 || j % space)
				ft_putchar(' ');
			j += 1;
			ft_putstr("\033[0m");
		}
		ft_putchar('\n');
		i += line;
	}
}
