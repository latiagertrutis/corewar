
#ifndef COREWAR_H
# define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>

#define HEADER_SIZE 4 + PROG_NAME_LENGTH + 1 + 4 + 4


typedef struct 		s_arena
{
	char 			board[MEM_SIZE];
}					t_arena;

typedef struct 		s_player
{
	char			*content;
	char 			*name;
	int				player_nb;
	char			*prog_size;
	char			*prog;
	char 			*comment;
}					t_player;


void				print_memory(const void *addr, size_t size, int line, int space);
void 				take_champions(int ac, char **av, t_player *players);
void 				big_hexa_2_dec(char *str, int size);
void				invert_bytes(void *arr, const size_t size);
int 				init_corewar(t_arena **arena, t_player **players, int ac);

#endif
