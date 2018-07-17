#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/04 20:25:41 by mrodrigu          #+#    #+#              #
#    Updated: 2018/07/14 09:02:38 by mrodrigu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean re

NAME = prueba

CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror -g3

CC = gcc

FUNCS =	main.c \
		big_hexa_2_dec.c \
		init_corewar.c \
		print_memory.c \
		get_content.c \
		invert_bytes.c \
		take_champions.c \
		put_champs_to_arena.c \
		free_players.c \
		put_usage.c \
		get_prog_size.c \
		read_alloc_size.c \
		print_board.c \
		exe_players.c \
		check_live_count.c \
		get_mem_board.c \
		fill_r1.c \
		# core_fork.c \
		# core_zjmp.c \
		# core_sti.c \
		# core_ld.c \
		# core_live.c \
		# core_st.c \
		# core_add.c \
		# core_and.c \
		# core_zjmp.c \


SRCS_DIR = srcs/

INC_DIR = includes/

LIBFT_DIR = libft/

LIBFT_NAME = libft.a

OBJ_DIR = objects/

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o,$(FUNCS))

INC = $(wildcard $(INC_DIR)*.h)

all: $(NAME)

.PHONY: $(LIBFT_DIR)$(LIBFT_NAME)

$(NAME): $(OBJ) | $(LIBFT_DIR)$(LIBFT_NAME)
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC)
	@mkdir -p $(OBJ_DIR)
	@printf "\033[92m--->Compiling $(@F)\033[0m"
	@$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@
	@printf "\033[92m   [OK]\n\033[0m"

$(LIBFT_DIR)$(LIBFT_NAME):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@printf "\033[92m***Cleaning Objects***\033[0m\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf "\033[92m***Cleaning Executables & Libraries***\033[0m\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	@make
