/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:48:39 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/10 11:50:32 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLIST_H
# define SLIST_H
# include <stdlib.h>

typedef struct	s_slist_elem
{
	size_t				len;
	char				*s;
	struct s_slist_elem	*prev;
	struct s_slist_elem	*next;
}				t_slist_elem;

typedef struct	s_slist
{
	t_slist_elem	*first;
	t_slist_elem	*last;
	size_t			len;
	size_t			total_len;
}				t_slist;

void			slist_create(t_slist *slist);
int				slist_push_front(t_slist *slist, char *s, size_t len);
void			slist_pop_back(t_slist *slist, char *dest, size_t *len);
char			*slist_join(t_slist *slist);

#endif
