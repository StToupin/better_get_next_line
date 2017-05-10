/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:22:44 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/05 11:02:32 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1024

typedef struct	s_openfile
{
	int					fd;
	int					first_call;
	int					eof;
	int					buf_size;
	char				buf[BUFF_SIZE + 1];
	char				*buf_pos;
	struct s_openfile	*next;
}				t_openfile;

int				get_next_line(const int fd, char **line);

#endif
