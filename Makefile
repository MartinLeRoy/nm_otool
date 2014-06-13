#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/27 21:01:48 by mle-roy           #+#    #+#              #
#    Updated: 2014/04/27 23:24:28 by mle-roy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_nm = ft_nm

NAME_O = ft_otool

SRC_nm = nm_64.c nm_main.c things.c get_sections.c new_thing.c offlist.c \
		swp_catch.c otool_fn.c

SRC_O = ft_otool.c offlist_tool.c swp_catch.c otool_fn.c browse_tool.c \
		archi_fat_tool.c

OBJ_nm = $(SRC_nm:.c=.o)

OBJ_O = $(SRC_O:.c=.o)

FLAGS = -g3 -Wall -Wextra -Werror

all: $(NAME_nm) $(NAME_O)

$(NAME_nm): $(OBJ_nm)
	@make -C libft
	@cc $(OBJ_nm) -L libft -lft -o $(NAME_nm)

$(NAME_O): $(OBJ_O)
	@cc $(OBJ_O) -L libft -lft -o $(NAME_O)

%.o: %.c
	@cc $(FLAGS) -c -I libft/includes  $<

clean:
	@/bin/rm -f $(OBJ_nm)
	@/bin/rm -f $(OBJ_O)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME_nm)
	@/bin/rm -f $(NAME_O)
	@make -C libft/ fclean

re: fclean all
