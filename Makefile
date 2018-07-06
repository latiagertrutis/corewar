#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/04 20:25:41 by mrodrigu          #+#    #+#              #
#    Updated: 2018/07/05 19:53:07 by mrodrigu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean re

NAME = prueba

CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror

CC = gcc

FUNCS =	main.c \
		big_hexa_2_dec.c \
		init_corewar.c \
		print_memory.c \
		get_content.c \
		invert_bytes.c \
		take_champions.c

SRCS_DIR = srcs/

INC_DIR = includes/

LIBFT_DIR = libft/

LIBFT_NAME = libft.a

OBJ_DIR = objects/

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o,$(FUNCS))

all: $(NAME)

.PHONY: $(LIBFT_DIR)$(LIBFT_NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT_NAME)
	gcc $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[92m--->Compiling $(@F)\033[0m\n"
	@$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@
	@printf "\033[92m   [OK]\n\033[0m\n"

$(LIBFT_DIR)$(LIBFT_NAME):
	$(MAKE) -sC $(LIBFT_DIR)

clean:
	@printf "\033[92m***Cleaning Objects***\033[0m\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "\033[92m***Cleaning Executables & Libraries***\033[0m\n"
	@rm -f $(NAME)

re: fclean
	@make
