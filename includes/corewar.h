
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
	unsigned int	prog_size;
	char			*prog;
	char 			*comment;
}					t_player;

typedef struct		s_data
{
	unsigned int	n_players;
	t_player		*players;
	t_arena			*arena;
}					t_data;

typedef struct		s_op
{
	char			*name;
	unsigned int	n_args;
	t_arg_type		*args;
	unsigned int	inst_id;
	unsigned int	mana;
	char			*comment;
	int				n1;
	int				n2;
}					t_op;

/*
**typedef struct		s_op
**{
**	char			*name; //nombre
**	unsigned int	n_args; //numero de argumentos del vector
**	t_arg_type		*args; //el vector
**	unsigned int	inst_id; //el id de la instruccion
**	unsigned int	mana; //los ciclos que consume
**	char			*comment; //comentario
**	int				n1; //no se sae loco
**	int				n2; //???
**}					t_op;
*/

void				print_memory(const void *addr, size_t size, int line, int space);
void 				take_champions(t_data *data, char **av);
void 				big_hexa_2_dec(char *str, int size);
void				invert_bytes(void *arr, const size_t size);
int 				init_corewar(t_data *data);
void				put_champs_to_arena(const t_data *data);

#endif
