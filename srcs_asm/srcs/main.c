#include "libasm.h"

static char	*namedotcor(char *av)
{
	char *r;
	int len;

	len = ft_strlen(av);
			/*	DELTE IF NEEDED		*/
	if (av[len - 1] != 's' || av[len - 2] != '.')
	{
		ft_invalidargv(1, av);
		return (NULL);
	}
	if (!(r = ft_strnew(len + 2)))
		return (NULL);
	r = ft_strcpy(r, av);
	r[len - 1] = 'c';
	r[len] = 'o';
	r[len + 1] = 'r';
	return (r);
}

int	main(int ac, char **av)
{
	int		fd;
	int		i;
	char	*filename;

	i = 0;
	if (ac == 1)
		return (ft_invalidargv(0, NULL));
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			return (ft_invalidargv(1, av[1]));
		if (!(filename = namedotcor(av[i])))
			exit (-1);
		if (assembler(fd, filename) == -1)
			exit (-1);
		ft_strdel(&filename);
	}
	return (0);
}
