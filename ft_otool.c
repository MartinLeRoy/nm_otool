/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 16:32:09 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:18:32 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "nm.h"

static int	errors(void)
{
	ft_putendl_fd("Error", 2);
	return (-1);
}

void		ft_otool(void *mem, char *name)
{
	struct mach_header_64	*mo;
	struct load_command		*com;
	unsigned int			number;

	mo = mem;
	com = mem + sizeof(struct mach_header_64);
	number = *(int *)mem;
	if (number == MH_MAGIC_64)
		browse_cmd(com, mo);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fati(mem);
	else if (!ft_strncmp(mem, ARMAG, SARMAG))
		go_archivi(mem, name);
	else
		ft_putendl("Wrong binary format");
}

static int	if_forest(int i, char **av)
{
	t_stat		stat;
	void		*mem;
	int			fd;

	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
		!(mem = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		ft_otool(mem, av[i]);
	if (fd != -1 && munmap(mem, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

void		printi_name(char *name)
{
	write(1, "\n", 1);
	ft_putstr(name);
	write(1, "\n", 1);
}

int			main(int ac, char **av)
{
	int		i;

	if (ac < 2)
		ft_putstr("bad argument\n");
	i = 1;
	while (i < ac)
	{
		printi_name(av[i]);
		if (!if_forest(i, av))
			break ;
		i++;
	}
	return (0);
}
