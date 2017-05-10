/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:50:36 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/10 11:50:38 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "slist.h"

static void	ft_strncpy(char *dest, char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

void		slist_create(t_slist *slist)
{
	slist->len = 0;
	slist->total_len = 0;
	slist->first = NULL;
	slist->last = NULL;
}

int			slist_push_front(t_slist *slist, char *s, size_t len)
{
	t_slist_elem	*element;

	element = (t_slist_elem*)malloc(sizeof(t_slist_elem)
									+ sizeof(char) * (len + 1));
	if (element == NULL)
		return (1);
	element->s = (void*)element + sizeof(t_slist_elem);
	ft_strncpy(element->s, s, len);
	element->s[len] = '\0';
	element->len = len;
	element->next = slist->first;
	element->prev = NULL;
	if (slist->len == 0)
		slist->last = element;
	else
		slist->first->prev = element;
	slist->first = element;
	slist->len++;
	slist->total_len += len;
	return (0);
}

void		slist_pop_back(t_slist *slist, char *dest, size_t *len)
{
	t_slist_elem	*element;

	*len = 0;
	if (slist->len == 0)
		return ;
	element = slist->last;
	slist->last = element->prev;
	if (slist->len == 1)
		slist->first = NULL;
	else
		slist->last->next = NULL;
	slist->len--;
	slist->total_len -= element->len;
	*len = element->len;
	ft_strncpy(dest, element->s, *len);
	free(element);
}

char		*slist_join(t_slist *slist)
{
	char	*joined;
	size_t	elem_len;
	size_t	copied;

	joined = (char*)malloc(sizeof(char) * (slist->total_len + 1));
	if (joined == NULL)
		return (NULL);
	copied = 0;
	while (slist->len > 0)
	{
		slist_pop_back(slist, joined + copied, &elem_len);
		copied += elem_len;
	}
	joined[copied] = '\0';
	return (joined);
}
