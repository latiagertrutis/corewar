#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/04 20:25:41 by mrodrigu          #+#    #+#              #
#    Updated: 2018/07/13 09:44:58 by jagarcia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean re check_lib

NAME = prueba

CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror -g3

SDLFLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_ttf

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
		core_live.c \
		check_live_count.c \
		fill_r1.c \
		flags.c

GRAPH = ft_ini_graphics.c \
		ft_quit_graphics.c \
		ft_SDL_error.c \
		ft_ini_board.c

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
	@$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@
	@printf "\033[92m   [OK]\n\033[0m"

$(OBJ_DIR)%.o: $(GRAPH_DIR)%.c $(INC) $(LIBFT_DIR)$(LIBFT_NAME)
	@mkdir -p $(OBJ_DIR)
	@printf "\033[92m--->Compiling $(@F)\033[0m"
	@$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@
	@printf "\033[92m   [OK]\n\033[0m"
else
$(NAME) : |check_lib $(OBJ)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(INC) $(LIBFT_DIR)$(LIBFT_NAME)
	@printf "\033[92mCreating $(NAME)\033[0m\n"
	@$(MAKE) MODE=1
	@printf "\033[92mDone $(NAME) [OK]\n\033[0m"
$(OBJ_DIR)%.o : $(GRAPH_DIR)%.c $(INC) $(LIBFT_DIR)$(LIBFT_NAME)
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
