/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 23:03:36 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/27 23:14:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <fcntl.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "list.h"
# include "libft.h"

typedef t_lsection			t_ls;
typedef struct nlist_64		t_l64;
typedef struct stat			t_stat;

void		ft_nm(char *ptr, char *name);
int			func_error();
t_things	*add_things(t_things *thing, struct nlist_64 list, char *strtable,
						t_lsection *sec);
t_things	*del_things(t_things *thing);
t_lsection	*get_section(struct load_command *cmd, struct mach_header_64 *mo);
char		secto(t_lsection *sec, unsigned int n_sect);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);

void		aff_things(t_things *thing);
void		browse_ar(t_offlist *lst, char *ptr, char *name);
int			catch_size(char *name);
void		print_addr(long unsigned int addr);
void		print_name(char *name);
uint32_t	swap_uint32(uint32_t val);
char		*catch_name(char *name);
void		ft_otool(void *mem, char *name);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
t_offlist	*add_offt(t_offlist *lst, uint32_t off, uint32_t strx);
void		print_art(uint32_t off, char *ptr, char *file);
void		browse_art(t_offlist *lst, char *ptr, char *name);
void		print_name(char *name);
void		print_addr(long unsigned int addr);
char		*ft_itoa_base(int val, int base, int output_size);
void		go_archivi(void *ptr, char *name);
void		go_fati(char *ptr);
void		browse_cmd(struct load_command *com, struct mach_header_64 *mo);

#endif
