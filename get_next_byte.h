/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_byte.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:22:44 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/05 11:02:32 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_BYTE_H
# define GET_NEXT_BYTE_H

# define BUFF_SIZE 1024

typedef struct	s_openfile
{
	int					fd;
	int					eof;
	int					buf_size;
	char				buf[BUFF_SIZE];
	char				*buf_pos;
}				t_openfile;

void			get_next_byte_init(t_openfile *file, int fd);
int				get_next_byte(t_openfile *file, char *byte);
void			write_next_byte(t_openfile *file, char byte);

#endif
