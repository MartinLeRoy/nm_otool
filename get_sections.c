/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/26 16:19:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 21:18:31 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "nm.h"

void		add_to_list(char *name, t_lsection *list)
{
	t_section	*add;

	if ((add = (t_section*)malloc(sizeof(t_section))) == NULL)
		return ;
	add->name = strdup(name);
	add->next = NULL;
	if (list->first == NULL)
	{
		list->first = add;
		list->last = add;
		add->nb = 1;
	}
	else
	{
		add->nb = list->last->nb + 1;
		list->last->next = add;
		list->last = add;
	}
}

void		add_seg(struct load_command *com, t_lsection *list)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		add_to_list(sec->sectname, list);
		sec = (struct section_64*)(((void*)sec)
									+ sizeof(struct section_64));
		i++;
	}
}

t_lsection	*get_section(struct load_command *com, struct mach_header_64 *mo)
{
	t_lsection			*list;
	unsigned int		i;

	i = 0;
	if ((list = (t_lsection*)malloc(sizeof(list))) == NULL)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	while (i < mo->ncmds)
	{
		if (com->cmd == LC_SEGMENT_64)
			add_seg(com, list);
		com += com->cmdsize / sizeof(void*);
		i++;
	}
	return (list);
}
