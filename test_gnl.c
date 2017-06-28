#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next.h"

int main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	t_openfile	of;
	t_openfile	of_out;

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
	get_next_init(&of, fd);
	get_next_init(&of_out, 1);
	while (get_next_line(&of, &line) == 1)
	{
		i = 0;
		while (line[i] != '\0')
		{
			write_next_byte(&of_out, line[i]);
			i++;
		}
		write_next_byte(&of_out, '\n');
		free(line);
	}
	of_out.eof = 1;
	write_next_byte(&of_out, 0);
	return (0);
}