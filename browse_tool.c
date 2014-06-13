/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:12:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:18:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "nm.h"

void	print_res(long unsigned int addr, unsigned int size, char *ptr)
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			print_addr(addr);
		}
		str = ft_itoa_base(ptr[i], 16, 2);
		write(1, str, 2);
		write(1, " ", 1);
		free(str);
		if ((i + 1) % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	check_text(struct segment_command_64 *seg, struct mach_header_64 *mo)
{
	struct section_64	*sec;
	unsigned int		i;

	i = 0;
	sec = (struct section_64*)(seg + sizeof(struct segment_command_64*)
							/ sizeof(void*));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, "__text")
			&& !ft_strcmp(sec->segname, "__TEXT"))
		{
			write(1, "(__TEXT,__text) section\n", 24);
			print_res(sec->addr, sec->size, (char *)mo + sec->offset);
		}
		sec = (struct section_64*)(((void*)sec)
								+ sizeof(struct section_64));
		i++;
	}
}

void	check_64(struct load_command *com, struct mach_header_64 *mo)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)com;
	check_text(seg, mo);
}

void	browse_cmd(struct load_command *com, struct mach_header_64 *mo)
{
	unsigned int	i;

	i = 0;
	while (i < mo->ncmds)
	{
		if (com->cmd == LC_SEGMENT_64)
			check_64(com, mo);
		com += com->cmdsize / sizeof(void *);
		i++;
	}
}
