#ifndef COREWAR_H
# define COREWAR_H

#define SDL_MAIN_HANDLED
#include "../SDL2_files/SDL2_srcs/include/SDL.h"
#include "../SDL2_files/SDL2_TTF_srcs/SDL_ttf.h"
#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <math.h>

#define HEADER_SIZE 4 + PROG_NAME_LENGTH + 1 + 4 + 4

#define MODE_SDL 1
#define MODE_TTF 0
#define SCREEN_W 1024
#define SCREEN_H 780
#define SCREEN_SCALE 1.2
#define SCREEN_NAME "Corewar"
#define LEFT_BORDER 0.357
#define BOTTOM_BORDER 0.033
#define UPPER_BORDER 0.033
#define RIGHT_BORDER 0.0180
#define RED_MASK 0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK 0x0000FF00
#define ALPHA_MASK 0x000000FF

typedef struct s_sdl {
	SDL_bool running;
	struct {
		int w;
		int h;
		const char *name;
		SDL_Window *window;
		SDL_Renderer *Renderer;
	} screen;
	int			cuant_squares[2];
	struct {
		TTF_Font *font;
		int		w;
		int		h;
	} font_info;
	SDL_Surface *rack;
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
	t_sdl			*Graph;
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
	unsigned short	pc;
	
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
	int				flags;
	void			(*func[16])(t_player *, t_op, t_arena *);
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
int					get_opc(t_board *board);

//Anyadidas Jaume
int					ft_set_flags(int argn, char **argv);
int					ft_check_flags(int flags, char flag);

/*
**------------------op_functions-----------------------------------
*/
void				core_live(t_player *player, t_op op, t_arena *arena);

/*
**------------------graphic_functions-----------------------------------
*/


void		ft_ini_graphics(t_sdl **Graph, int flags);
void		ft_quit_graphics(t_sdl *Graph);
void		ft_SDL_error(char *str, int mode);
void		ft_ini_interface(t_sdl *Graph);
void		ft_ini_font(t_sdl *Graph);
void		ft_board_to_screen(t_sdl *Graph, t_board board[MEM_SIZE]);
void		ft_pcs_to_screen(t_sdl *Graph, t_player *player, int n_players);
#endif
