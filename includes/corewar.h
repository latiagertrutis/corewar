
#ifndef COREWAR_H
# define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>

#define HEADER_SIZE 4 + PROG_NAME_LENGTH + 1 + 4 + 4
#define PC_BUFF 20
#define MAX_ARG_LEN 4

typedef struct		s_arg
{
	unsigned char	n_arg;
	unsigned char	len;
	unsigned char	type;
	unsigned char	arg[MAX_ARG_LEN];
}					t_arg;




typedef struct 		s_board
{
	unsigned char 	mem;
	char			id;
}					t_board;

typedef struct 		s_arena
{
	t_board			board[MEM_SIZE];
}					t_arena;

typedef struct 		s_player
{
	char 			reg[REG_NUMBER][REG_SIZE];
	unsigned int 	live_counter;
	unsigned int	carry : 1;
	char			*content;
	char 			*name;
	int				player_nb;
	char 			id;
	unsigned int	prog_size;
	char			*prog;
	char 			*comment;
	int 			wait_cycles;
	unsigned short	*pc;
}					t_player;

typedef struct		s_op
{
	char			*name;
	unsigned int	n_args;
	t_arg_type		args[3];
	unsigned int	inst_id;
	unsigned int	mana;
	char			*comment;
	int				n1;
	int				n2;
}					t_op;

typedef struct		s_data
{
	unsigned int	n_players;
	t_player		*players;
	t_arena			*arena;
	char 			palete[5][10];
	t_op 			op[17];
	unsigned int	nb_cycles;
	void			(*func[16])(t_player *, unsigned short *, t_arena *);
}					t_data;

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
void 				free_players(t_player *player, int nb_players);
void				put_usage();
unsigned int		get_prog_size(int fd);
char 				*read_alloc_size(int fd, int size);
void				print_board(t_data *data, t_board *board);
void 				exe_players(t_data *data);
void				check_live_count(t_player *players, int nb_players);
void				fill_r1(t_data *data);
unsigned char		*get_mem_board(t_board *board, const unsigned int size);


/*
**------------------op_functions-----------------------------------
*/
void				core_live(t_player *player, unsigned short *pc, t_arena *arena);
void 				core_sti(t_player *player, unsigned short *pc, t_arena *arena);
void				core_ld(t_player *player, unsigned short *pc, t_arena *arena);
void				core_st(t_player *player, unsigned short *pc, t_arena *arena);
void				core_add(t_player *player, unsigned short *pc, t_arena *arena);
void				core_and(t_player *player, unsigned short *pc, t_arena *arena);
void				core_zjmp(t_player *player, unsigned short *pc, t_arena *arena);
void				core_fork(t_player *player, unsigned short *pc, t_arena *arena);

#endif
