# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/12 00:00:00 by raisufaj          #+#    #+#              #
#    Updated: 2026/11/12 00:00:00 by raisufaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ft_printf.c print_base.c print_char.c print_int.c print_string.c
OBJS	= $(SRCS:.c=.o)
LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# Builds main.c against the real printf and against ft_printf, then diffs the output.
test: $(NAME)
	$(CC) $(CFLAGS) -D PRINTF=printf main.c -o std.out
	$(CC) $(CFLAGS) -D PRINTF=ft_printf main.c $(NAME) -o ft.out
	./std.out > std.txt && ./ft.out > ft.txt && diff std.txt ft.txt && echo "test: OK"

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS) std.out ft.out std.txt ft.txt

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
