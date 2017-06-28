/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:56:11 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/26 14:56:12 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "get_next_byte.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	write(1, str, i);
}

void	print_usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" file_name\n");
}

int		main(int argc, char **argv)
{
	int			fd;
	t_openfile	of;
	t_openfile	of_out;
	char		byte;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr("Error opening '");
			ft_putstr(argv[1]);
			ft_putstr("'.\n");
			return (1);
		}
		get_next_byte_init(&of, fd);
		get_next_byte_init(&of_out, 1);
		while (get_next_byte(&of, &byte) == 1)
			write_next_byte(&of_out, byte);
		of_out.eof = 1;
		write_next_byte(&of_out, 0);
	}
	else
		print_usage(argv[0]);
	return (0);
}
