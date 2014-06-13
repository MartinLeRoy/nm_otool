/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_thing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 21:01:35 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:22:38 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "nm.h"

t_things	*add_before(t_things *yolo, t_things *to_add)
{
	t_things	*ret;

	ret = NULL;
	if (yolo->prev == NULL)
	{
		yolo->prev = to_add;
		to_add->next = yolo;
		ret = to_add;
	}
	else
	{
		to_add->next = yolo;
		to_add->prev = yolo->prev;
		yolo->prev->next = to_add;
		yolo->prev = to_add;
	}
	return (ret);
}

void		add_tail(t_things *yolo, t_things *to_add)
{
	to_add->prev = yolo;
	yolo->next = to_add;
}

char		typing(unsigned int type, unsigned int n_sect, t_ls *sec, int addr)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

t_things	*init_thg(struct nlist_64 list, char *str, t_lsection *sec)
{
	t_things	*tmp;

	tmp = (t_things*)malloc(sizeof(t_things));
	tmp->value = list.n_value;
	tmp->type = typing(list.n_type, list.n_sect, sec, list.n_value);
	tmp->str = ft_strdup(str + list.n_un.n_strx);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_things	*add_things(t_things *thing, t_l64 list, char *str, t_ls *sec)
{
	t_things	*bws_word;
	t_things	*tmp;
	t_things	*ret;

	tmp = init_thg(list, str, sec);
	if (thing == NULL)
		return (tmp);
	bws_word = thing;
	while (bws_word)
	{
		if (ft_strcmp(bws_word->str, tmp->str) > 0)
		{
			ret = add_before(bws_word, tmp);
			if (ret)
				thing = ret;
			break ;
		}
		else if (bws_word->next == NULL)
		{
			add_tail(bws_word, tmp);
			break ;
		}
		bws_word = bws_word->next;
	}
	return (thing);
}
