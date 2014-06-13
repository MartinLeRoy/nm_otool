/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archi_fat_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:09:20 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:10:52 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	go_fati(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			x;
	uint32_t			offset;

	fat = (void*)ptr;
	x = fat->nfat_arch;
	x = swap_uint32(x);
	arch = (void*)ptr + sizeof(fat);
	while (x)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		x--;
	}
	ft_otool(ptr + swap_uint32(offset), NULL);
}

void	go_archivi(void *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_offt(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_art(lst, ptr, name);
}
