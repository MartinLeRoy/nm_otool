/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:26:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:26:44 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	end_nm(struct symtab_command *sym, char *ptr, t_lsection *sec)
{
	unsigned int		i;
	char				*strtable;
	t_l64				*list;
	t_things			*thing;

	i = 0;
	list = (void *)ptr + sym->symoff;
	thing = NULL;
	strtable = (void *)ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0
				&& strtable + list[i].n_un.n_strx && ft_strlen(strtable +
				list[i].n_un.n_strx) && list[i].n_type != 100)
			thing = add_things(thing, list[i], strtable, sec);
		i++;
	}
	thing = del_things(thing);
	aff_things(thing);
}

void	find_oct(char *ptr)
{
	int						cmd;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*command;
	struct symtab_command	*sym;
	t_lsection				*sec;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	cmd = header->ncmds;
	command = (void *)ptr + sizeof(*header);
	sec = get_section(command, header);
	while (i < cmd)
	{
		if (command->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)command;
			end_nm(sym, ptr, sec);
			break ;
		}
		command = (void *)command + command->cmdsize;
		i++;
	}
}

void	go_fat(char *ptr)
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
	ft_nm(ptr + swap_uint32(offset), NULL);
}

void	go_archive(char *ptr, char *name)
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
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_ar(lst, ptr, name);
}

void	ft_nm(char *ptr, char *name)
{
	unsigned int		number;

	number = *(int *)ptr;
	if (number == MH_MAGIC_64)
		find_oct(ptr);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		go_archive(ptr, name);
	else
		ft_putendl("Wrong binary format");
}
