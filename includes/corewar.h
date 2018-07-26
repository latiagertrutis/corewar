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
#define MAX_ARG_LEN REG_SIZE

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
/* #define LEFT_BORDER 0.3567 */
/* #define BOTTOM_BORDER 0.0328 */
/* #define UPPER_BORDER 0.033 */
/* #define RIGHT_BORDER 0.0180 */
#define LEFT_BORDER 0.434
#define BOTTOM_BORDER 0.055
#define UPPER_BORDER 0.055
#define RIGHT_BORDER 0.04
//#define BACK_COLOR 28, 28, 21,
#define BACK_COLOR 0, 0, 0,
#define FIELD_COLOR 61, 61, 51,

typedef	struct	s_info
{
	SDL_Surface *cicles;
	SDL_Surface *lifes;
	SDL_Surface *lst_life;
}				t_info;

typedef struct s_font
{
	TTF_Font	*font;
	int			font_size;
	int			w;
	int			h;
}				t_font;

typedef struct s_sdl {
	struct {
		int w;
		int h;
		const char *name;
		SDL_Window *window;
		SDL_Renderer *Renderer;
		SDL_Texture *texture;
	} screen;
	int			cuant_squares[2];
	t_font	font[2];
	SDL_Texture *info_text;
	SDL_Texture **pc;
	struct {
		SDL_Surface *cicles;
		SDL_Surface *cicle_to_die;
	} general_info;
	t_info		player_info[4];
	SDL_Surface ***hexa_bytes;
	SDL_Surface *rack;
	SDL_Rect *square;
	SDL_Rect *big_square;
	SDL_Rect *square_info;
} t_sdl;

typedef struct 		s_board
{
	unsigned char 	mem;
	char			id;
	unsigned int	new : 1;
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
	char 			id;
}					t_pc;

typedef struct 		s_player
{
	unsigned int  	last_live; //new
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

typedef struct		s_mods
{
	unsigned int	running : 1;
	unsigned int	pause : 1;
	unsigned int	step : 1;
	unsigned int	visual : 1;
	unsigned int	fullscreen : 1;
}					t_mods;

typedef struct		s_data
{
	unsigned int 	dump;
	unsigned int 	max_checks;
	int 			cycle_to_die;
	unsigned int	n_players;
	t_player		*players;
	t_arena			*arena;
	char 			palete[5][10];
	t_op 			op[17];
	unsigned int	nb_cycles;
	int				flags;
	int				i;
	t_mods			*mods;
	// void			(*func[16])(t_player *, t_pc *, t_arena *, struct s_data *);
	void			(*func[16])(t_pc *, t_arena *, struct s_data *);
	unsigned int 	nb_pc;
	t_pc			*pc;

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
void 				take_champions(t_data *data, char **av, int i);
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
void 				check_live_count(t_player *players, int nb_players, t_data *data);
void				fill_r1(t_data *data);
unsigned char		*get_mem_board(t_board *board, const unsigned int size);
t_pc				*realloc_pc(t_pc *pc, const unsigned int nb_pc);
unsigned char		get_size_arg(const unsigned char ocp, const unsigned char n_arg, const unsigned int dir_size);
void				get_arg(const unsigned char ocp, unsigned short pos, t_board *board, t_arg *arg);
int					get_arg_value(t_board *board, t_arg *arg, t_pc *pc);
int					ft_mod(const int nb, const unsigned int mod);
void 				check_winner(t_player *players, int nb_players);
unsigned char		check_ocp(const unsigned char ocp);


//Anyadidas Jaume
int					ft_set_flags(int argn, char **argv, t_data *data);
int					ft_check_flags(int flags, char flag);


/*
**------------------op_functions-----------------------------------
*/
void				core_live(t_pc *pc, t_arena *arena, t_data *data);
void				core_ld(t_pc *pc, t_arena *arena, t_data *data);
void				core_st(t_pc *pc, t_arena *arena, t_data *data);
void				core_add(t_pc *pc, t_arena *arena, t_data *data);
void				core_sub(t_pc *pc, t_arena *arena, t_data *data);
void				core_and(t_pc *pc, t_arena *arena, t_data *data);
void				core_or(t_pc *pc, t_arena *arena, t_data *data);
void				core_xor(t_pc *pc, t_arena *arena, t_data *data);
void				core_zjmp(t_pc *pc, t_arena *arena, t_data *data);
void 				core_ldi(t_pc *pc, t_arena *arena, t_data *data);
void 				core_sti(t_pc *pc, t_arena *arena, t_data *data);
void				core_fork(t_pc *pc, t_arena *arena, t_data *data);
void				core_lfork(t_pc *pc, t_arena *arena, t_data *data);
void				core_lld(t_pc *pc, t_arena *arena, t_data *data);
void				core_lldi(t_pc *pc, t_arena *arena, t_data *data);
void				core_aff(t_pc *pc, t_arena *arena, t_data *data);


/*
**------------------graphic_functions-----------------------------------
*/


void		ft_ini_graphics(t_sdl **Graph, t_mods *mods, t_data *data);
void		ft_quit_graphics(t_sdl *Graph);
void		ft_SDL_error(char *str, int mode);
void		ft_ini_interface(t_sdl *Graph);
void		ft_ini_font(t_sdl *Graph);
void		ft_board_to_screen(t_sdl *Graph, t_board board[MEM_SIZE], t_data *data);
void		ft_pcs_to_rack(t_sdl *Graph, t_data *data, int alpha_mod);
void		ft_set_back_to_front(t_sdl *Graph, t_data *data);
//void		ft_ini_information(t_data *data);
//void		ft_ini_material(t_data *data, t_sdl *Graph);


#endif
