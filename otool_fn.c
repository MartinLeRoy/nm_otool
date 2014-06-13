/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:04:01 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:08:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "nm.h"

char		read_tab(int i)
{
	char	*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

char		*ft_itoa_base(int val, int base, int output_size)
{
	char			buffer[output_size + 1];
	char			*p;
	unsigned int	unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

char		*ft_adresstostr(long unsigned int n)
{
	char		*new;
	char		*tmp;
	int			l;
	char		c;
	char		*table;

	tmp = ft_strdup("00000000000000000000000000000000");
	table = ft_strdup("0123456789abcdefghijklmnopqrstuvwxyz");
	l = 31;
	if (n == 0)
		l--;
	else
	{
		while (n != 0)
		{
			c = table[(n % 16)];
			tmp[l--] = c;
			n = n / 16;
		}
	}
	new = ft_strsub(tmp, (l + 1), ft_strlen(&tmp[l]));
	free(tmp);
	free(table);
	return (new);
}

void		print_addr(long unsigned int addr)
{
	char	*tmp;
	int		len;

	tmp = ft_adresstostr(addr);
	len = 16 - ft_strlen(tmp);
	write(1, "0000000000000000", len);
	write(1, tmp, ft_strlen(tmp));
	write(1, " ", 1);
	free(tmp);
}
