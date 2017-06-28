/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:22:11 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/05 10:23:34 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "slist.h"
#include "get_next_line.h"

void			get_next_line_init(t_openfile *of, int fd)
{
	of->fd = fd;
	of->buf_size = 0;
	of->buf_pos = of->buf;
	of->eof = 0;
}

static int		expand_str(t_slist *slist, t_openfile *of)
{
	int		keep_on_reading;
	size_t	i;

	keep_on_reading = 1;
	i = 0;
	while (of->buf_pos + i < of->buf + of->buf_size && keep_on_reading)
	{
		if (of->buf_pos[i] == '\n')
			keep_on_reading = 0;
		else
			i++;
	}
	slist_push_front(slist, of->buf_pos, i);
	of->buf_pos += i + 1;
	return (keep_on_reading);
}

int				get_next_line(t_openfile *of, char **line)
{
	t_slist				slist;

	if (of == NULL || of->fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	slist_create(&slist);
	while (of->eof == 0 && expand_str(&slist, of))
	{
		if ((of->buf_size = read(of->fd, of->buf, BUFF_SIZE)) == -1)
			return (-1);
		of->buf_pos = of->buf;
		of->eof = (of->buf_size == 0);
	}
	if (slist.len == 0 && of->eof == 0)
		return (-1);
	if (of->eof && slist.len == 0)
		return (0);
	*line = slist_join(&slist);
	return (1);
}

void			write_next_line(t_openfile *of, char *line)
{
	if (of == NULL || of->fd < 0 || (line == NULL && of->eof != 1))
		return ;
	if (of->eof == 1 && of->buf_size > 0)
	{
		write(of->fd, of->buf, of->buf_size);
		return ;
	}
	while (*line != '\0')
	{
		*(of->buf_pos)++ = *line++;
		of->buf_size++;
		if (of->buf_size == BUFF_SIZE)
		{
			write(of->fd, of->buf, of->buf_size);
			of->buf_size = 0;
			of->buf_pos = of->buf;
		}
	}
	*(of->buf_pos)++ = '\n';
	of->buf_size++;
	if (of->buf_size == BUFF_SIZE)
	{
		write(of->fd, of->buf, of->buf_size);
		of->buf_size = 0;
		of->buf_pos = of->buf;
	}
}
