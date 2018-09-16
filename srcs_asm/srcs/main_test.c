#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define SIZE_READ 1000

int	main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	s1[SIZE_READ];
	char	s2[SIZE_READ];
	int		i;
	char	*filename;

	i = -1;
	while (++i < SIZE_READ)
	{
		s1[i] =  0;
		s2[i] =  0;
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	if ((fd2 = open(av[2], O_RDONLY)) == -1)
		return (0);
	read(fd, s1, SIZE_READ);
	read(fd2, s2, SIZE_READ);
	i = -1;
	while (++i < SIZE_READ)
	{
		write(1, "*", 1);
//		if (s1[i] != s2[i])
//		{
//			write(1, "CACA", 4);
//			return (0);
//		}
	}
	write(1, "OK!!", 4);
	return (0);
}
