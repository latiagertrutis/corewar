#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/04 20:25:41 by mrodrigu          #+#    #+#              #
#    Updated: 2018/09/23 17:50:43 by mrodrigu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean re check_lib

NAME = prueba

CFLAGS = -pthread  #-g3 #-fsanitize=address #-Wall -Wextra -Werror -g3

CC = gcc

FUNCS =	main.c \
		init_player.c \
		invert_bytes.c \
		read_alloc.c \
		set_flags.c \
		take_input.c \
		check_cycle_to_die.c \
		ft_mod.c \
		get_size_arg.c \
		get_arg.c \
		get_arg_value.c \
		basic_launch.c \
		graphic_launch.c \
		core_live.c \
		core_ld.c \
		core_st.c \
		core_add.c \
		core_sub.c \
		core_and.c \
		core_or.c \
		core_xor.c \
		core_zjmp.c \
		core_ldi.c \
		core_sti.c \
		core_fork.c \
		core_lld.c \
		core_lldi.c \
		core_lfork.c \
		core_aff.c \

SRCS_DIR = srcs/

GRAPH_DIR = srcs_graphics/

INC_DIR = includes/

LIBFT_DIR = libft/

LIBFT_NAME = libft.a

OBJ_DIR = objects/

OBJ_FUNCS = $(patsubst %.c, $(OBJ_DIR)%.o,$(FUNCS))

OBJ_GRAPH = $(patsubst %.c, $(OBJ_DIR)%.o, $(GRAPH))

INC = $(wildcard $(INC_DIR)*.h)

OBJ = $(OBJ_FUNCS) $(OBJ_GRAPH)

MODE = 0

ifeq ($(MODE), 1)
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(SDLFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC) $(LIBFT_DIR)$(LIBFT_NAME)
	@mkdir -p $(OBJ_DIR)
	@printf "\033[92m--->Compiling $(@F)\033[0m"
	@$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -I$(LIBFT_DIR)includes/ -o $@
	@printf "\033[92m   [OK]\n\033[0m"

else
$(NAME) : |check_lib $(OBJ)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(INC) $(LIBFT_DIR)$(LIBFT_NAME)
	@printf "\033[92mCreating $(NAME)\033[0m\n"
	@$(MAKE) MODE=1
	@printf "\033[92mDone $(NAME) [OK]\n\033[0m"
endif

check_lib:
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
