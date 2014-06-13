/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/25 18:52:34 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 19:15:11 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct			s_things
{
	long int			value;
	char				type;
	char				*str;
	struct s_things		*next;
	struct s_things		*prev;
}						t_things;

typedef struct			s_section
{
	char				*name;
	unsigned int		nb;
	struct s_section	*next;
}						t_section;

typedef struct			s_lsection
{
	t_section			*first;
	t_section			*last;
}						t_lsection;

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

#endif
