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
#include "get_next.h"

static char	*ft_strndup(char *str, int n)
{
	char	*new_str;
	int		i;

	new_str = (char*)malloc(sizeof(char) * (n + 1));
	if (new_str != NULL)
	{
		i = 0;
		while (i < n)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

static int	slist_delete(t_slist *slist)
{
	t_slist_elem	*element;

	while (slist->len > 0)
	{
		element = slist->last;
		slist->last = element->prev;
		if (slist->len == 1)
			slist->first = NULL;
		else
			slist->last->next = NULL;
		slist->len--;
		slist->total_len -= element->len;
	}
	return (1);
}

static int	find_line_break(char *s, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

int			get_from_single_buffer(t_openfile *of, int line_break_pos,
																	char **line)
{
	*line = ft_strndup(of->buf_pos, line_break_pos);
	of->buf_pos += line_break_pos + 1;
	return (*line == NULL ? -1 : 1);
}

int			get_next_line(t_openfile *of, char **line)
{
	t_slist	slist;
	int		line_break_pos;
	int		size_left;

	if (of->fd < 0 || line == NULL || of->eof == 1)
		return (-1 * (of->eof != 1));
	size_left = of->buf_size - (of->buf_pos - of->buf);
	if ((line_break_pos = find_line_break(of->buf_pos, size_left)) < size_left)
		return (get_from_single_buffer(of, line_break_pos, line));
	slist_create(&slist);
	while (of->eof == 0)
	{
		if (slist_push_front(&slist, of->buf_pos, line_break_pos) == 1)
			return (-slist_delete(&slist));
		of->buf_pos = of->buf + line_break_pos + 1;
		if (line_break_pos < size_left)
			break ;
		if ((size_left = read(of->fd, of->buf, BUFF_SIZE)) == -1)
			return (-slist_delete(&slist));
		of->buf_pos = of->buf;
		of->buf_size = size_left;
		of->eof = (size_left == 0);
		line_break_pos = find_line_break(of->buf, size_left);
	}
	return ((*line = slist_join(&slist)) == NULL ? -1 : 1);
}
