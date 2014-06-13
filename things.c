/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:27:45 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:27:46 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "nm.h"

char		secto(t_lsection *sec, unsigned int n_sect)
{
	t_section	*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

void		print_w_add(long int val, char type, char *str)
{
	print_addr(val);
	write(1, &type, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void		aff_things(t_things *thing)
{
	t_things	*tmp;

	tmp = thing;
	while (tmp)
	{
		if (tmp->value)
			print_w_add(tmp->value, tmp->type, tmp->str);
		else
		{
			write(1, "\t\t ", 3);
			write(1, &(tmp->type), 1);
			write(1, " ", 1);
			write(1, tmp->str, ft_strlen(tmp->str));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

t_things	*del_things(t_things *thing)
{
	t_things	*tmp;
	t_things	*tmp2;

	tmp = thing;
	while (tmp)
	{
		if ((tmp->type == 'z' || tmp->type == 'Z')
			|| (tmp->next && tmp->value && tmp->value == tmp->next->value))
		{
			if (tmp->type != 'z' && tmp->type != 'Z' && tmp->next->type == '?')
				tmp = tmp->next;
			tmp2 = tmp->next;
			if (tmp2)
				tmp2->prev = tmp->prev;
			tmp->prev->next = tmp2;
			free(tmp->str);
			free(tmp);
		}
		tmp = tmp->next;
	}
	return (thing);
}
