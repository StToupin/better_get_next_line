#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		i;

	if (argc != 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening '%s'.\n", argv[1]);
		return (0);
	}
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		printf("%03d %s\n", i + 1, line);
		free(line);
		i++;
	}
	return (0);
}