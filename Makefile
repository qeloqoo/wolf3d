# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/04 18:28:04 by mdubrovs          #+#    #+#              #
#    Updated: 2017/03/04 18:28:12 by mdubrovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FLAGS = -Wall -Wextra -Werror -g
FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit
SRCS = main.c draw_procedures.c controls.c raycast.c read_level.c
HEADERS = wolf3d.h
BINS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_MLX) libft/libft.a minilibx/libmlx.a

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean: 
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
