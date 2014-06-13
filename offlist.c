/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:27:05 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:27:06 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "nm.h"

t_offlist		*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (lst);
}

void			print_file_name(char *file, char *name)
{
	write(1, "\n", 1);
	write(1, file, ft_strlen(file));
	write(1, "(", 1);
	write(1, name, ft_strlen(name));
	write(1, "):", 2);
	write(1, "\n", 1);
}

void			print_ar(uint32_t off, char *ptr, char *file)
{
	int				size_fuck;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size_fuck = catch_size(arch->ar_name);
	print_file_name(file, name);
	ft_nm((void*)arch + sizeof(*arch) + size_fuck, file);
}

void			browse_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
