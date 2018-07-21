#ifndef COREWAR_H
# define COREWAR_H

#define SDL_MAIN_HANDLED
#include "../SDL2_files/SDL2_srcs/include/SDL.h"
#include "../SDL2_files/SDL2_TTF_srcs/SDL_ttf.h"
#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <math.h>
#include <pthread.h>

#define HEADER_SIZE 4 + PROG_NAME_LENGTH + 1 + 4 + 4
#define PC_BUFF 20
#define MAX_ARG_LEN 4

typedef struct		s_arg
{
	unsigned char	n_arg;
	unsigned char	len;
	unsigned char	type;
	unsigned int	dir_size : 1; //1 for D4 0 for D2
	unsigned char	arg[MAX_ARG_LEN];
}					t_arg;

#define MODE_SDL 1
#define MODE_TTF 0
#define SCREEN_W 1280
#define SCREEN_H 800
#define SCREEN_SCALE 1.2
#define SCREEN_NAME "Corewar"
#define LEFT_BORDER 0.3567
#define BOTTOM_BORDER 0.0328
#define UPPER_BORDER 0.033
#define RIGHT_BORDER 0.0180
#define BACK_COLOR 28, 28, 21,
#define FIELD_COLOR 61, 61, 51,
typedef struct s_sdl {
	SDL_bool running;
	struct {
		int w;
		int h;
		const char *name;
		SDL_Window *window;
		SDL_Renderer *Renderer;
		SDL_Texture *texture;
		SDL_Surface *screen;
	} screen;
	int			cuant_squares[2];
	struct {
		TTF_Font *font;
		int		w;
		int		h;
	} font_info;
	SDL_Surface	*character_buffer;
	SDL_Surface *rack;
	SDL_Surface *rack_square;
	SDL_Rect *square;
} t_sdl;

typedef struct 		s_board
{
	unsigned char 	mem;
	char			id;
}					t_board;

typedef struct 		s_arena
{
	t_board			board[MEM_SIZE];
	t_board			lst_board[MEM_SIZE];
	t_sdl			*Graph;
}					t_arena;

typedef struct 		s_pc
{
	unsigned int	carry : 1;
	unsigned short	pc;
	size_t 			wait_cycles;
	char 			reg[REG_NUMBER][REG_SIZE];
}					t_pc;

typedef struct 		s_player
{
	unsigned int 	live_counter;
	char			*content;
	char 			*name;
	int				player_nb;
	char 			id;
	unsigned int	prog_size;
	char			*prog;
	char 			*comment;
	unsigned int 	nb_pc;
	t_pc 			*pc;
}					t_player;

//hay que hacer una estructura del PC que contenga minimo 1 pc(pos) 2 carry, wait_cycles

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
	int				flags;
	int				i;
	void			(*func[16])(t_player *, t_pc *, t_arena *);
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
t_pc				*realloc_pc(t_player *player, t_pc *pc, const unsigned int nb_pc);
unsigned char		get_size_arg(const unsigned char ocp, const unsigned char n_arg, const unsigned int dir_size);
void				get_arg(const unsigned char ocp, unsigned short pos, t_board *board, t_arg *arg);
void				get_arg_value(t_board *board, t_arg *arg, t_pc *pc);
int					ft_mod(const int nb, const unsigned int mod);

//Anyadidas Jaume
int					ft_set_flags(int argn, char **argv);
int					ft_check_flags(int flags, char flag);

/*
**------------------op_functions-----------------------------------
*/
void				core_live(t_player *player, t_pc *pc, t_arena *arena);
void				core_ld(t_player *player, t_pc *pc, t_arena *arena);
void				core_st(t_player *player, t_pc *pc, t_arena *arena);
void				core_add(t_player *player, t_pc *pc, t_arena *arena);
void				core_sub(t_player *player, t_pc *pc, t_arena *arena);
void				core_and(t_player *player, t_pc *pc, t_arena *arena);
void				core_or(t_player *player, t_pc *pc, t_arena *arena);
void				core_xor(t_player *player, t_pc *pc, t_arena *arena);
void				core_zjmp(t_player *player, t_pc *pc, t_arena *arena);
void 				core_ldi(t_player *player, t_pc *pc, t_arena *arena);
void 				core_sti(t_player *player, t_pc *pc, t_arena *arena);
void				core_fork(t_player *player, t_pc *pc, t_arena *arena);
void				core_lfork(t_player *player, t_pc *pc, t_arena *arena);
void				core_lld(t_player *player, t_pc *pc, t_arena *arena);
void				core_lldi(t_player *player, t_pc *pc, t_arena *arena);
void				core_aff(t_player *player, t_pc *pc, t_arena *arena);


/*
**------------------graphic_functions-----------------------------------
*/


void		ft_ini_graphics(t_sdl **Graph, int flags);
void		ft_quit_graphics(t_sdl *Graph);
void		ft_SDL_error(char *str, int mode);
void		ft_ini_interface(t_sdl *Graph);
void		ft_ini_font(t_sdl *Graph);
void		ft_board_to_screen(t_sdl *Graph, t_arena *arena);
void		ft_pcs_to_screen(t_data *data, t_sdl *Graph, t_player *players);
void		ft_write_byte(int pos, t_board byte, t_sdl *Graph);
void		ft_draw_rack(t_data *data, SDL_Surface *screen);
#endif
