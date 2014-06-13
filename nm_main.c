/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:58:47 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 22:58:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "nm.h"

int				errors(void)
{
	ft_putendl_fd("Error", 2);
	return (-1);
}

void			print_name(char *name)
{
	write(1, "\n", 1);
	ft_putstr(name);
	write(1, "\n", 1);
}

static int		if_forest(int ac, int i, char **av)
{
	t_stat		stat;
	char		*ptr;
	int			fd;

	if (ac > 2)
		print_name(av[i]);
	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
		!(ptr = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		ft_nm(ptr, av[i]);
	if (fd != -1 && munmap(ptr, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	int		i;

	if (ac < 2)
	{
		av[1] = ft_strdup("a.out");
		ac = 2;
	}
	i = 1;
	while (i < ac)
	{
		if (!if_forest(ac, i, av))
			break ;
		i++;
	}
	return (0);
}
