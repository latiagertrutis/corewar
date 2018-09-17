#ifndef COREWAR_H
# define COREWAR_H

#define SDL_MAIN_HANDLED
#include "../SDL2_files/SDL2_srcs/include/SDL.h"
#include "../SDL2_files/SDL2_TTF_srcs/SDL_ttf.h"
#include "../SDL2_files/SDL2_image_srcs/SDL_image.h"
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
#define MODE_IMG -1
#define FIELD_FONT 0
#define TMP_FONT 1
#define GENERAL_NBR_FONT 2
#define PLAYER_NBR_FONT 3
#define SCREEN_W 1280
#define SCREEN_H 800
#define SCREEN_SCALE 1.2
#define SCREEN_NAME "Corewar"
#define LEFT_BORDER 0.434
#define BOTTOM_BORDER 0.055
#define UPPER_BORDER 0.055
#define RIGHT_BORDER 0.04
#define NEW_COLOR_CYCLES 70
#define NONE_COLOR 89, 89, 75, SDL_ALPHA_OPAQUE
#define PLAYER_ONE_COLORA 51, 255, 51, SDL_ALPHA_OPAQUE
#define PLAYER_ONE_COLORB 153, 255, 153, SDL_ALPHA_OPAQUE
#define PLAYER_ONE_COLORC 0, 153, 0, SDL_ALPHA_OPAQUE
#define PLAYER_TWO_COLORA 255, 204, 0, SDL_ALPHA_OPAQUE
#define PLAYER_TWO_COLORB 255, 229, 127, SDL_ALPHA_OPAQUE
#define PLAYER_TWO_COLORC 127, 102, 0, SDL_ALPHA_OPAQUE
#define PLAYER_THREE_COLORB 255, 242, 207, SDL_ALPHA_OPAQUE
#define PLAYER_THREE_COLORA 217, 204, 169, SDL_ALPHA_OPAQUE
#define PLAYER_THREE_COLORC 168, 154, 117, SDL_ALPHA_OPAQUE
#define PLAYER_FOUR_COLORA 252, 102, 92, SDL_ALPHA_OPAQUE
#define PLAYER_FOUR_COLORB 253, 178, 173, SDL_ALPHA_OPAQUE
#define PLAYER_FOUR_COLORC 176, 4, 0, SDL_ALPHA_OPAQUE
#define BACK_COLOR 0, 0, 0, SDL_ALPHA_OPAQUE
#define FIELD_COLOR 61, 61, 51, SDL_ALPHA_OPAQUE

typedef struct s_font
{
	TTF_Font	*font;
	int			font_size;
	int			w;
	int			h;
	SDL_Color	color;
}				t_font;

typedef	struct s_info
{
	SDL_Rect *cicles_gen;
	SDL_Rect *cicles_play;
	SDL_Rect *lst_life;
	SDL_Rect *cicle_to_die;
	SDL_Rect *processos;
} t_info;

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
	t_font	font[4];
	SDL_Texture *info_text;
	SDL_Texture **pc;
	t_info info;
	SDL_Surface ***hexa_bytes;
	SDL_Surface *rack;
	SDL_Surface *general_nbr;
	SDL_Surface *player_nbr;
	SDL_Surface **heart;
	SDL_Rect *heart_pos;
	SDL_Rect *square;  // rack_cell;
	SDL_Rect *big_square; // board
	SDL_Rect *square_info; // general info
	SDL_Rect *info_marc; // player_info
} t_sdl;

typedef struct 		s_board
{
	unsigned char 	mem;
	char			id;
	unsigned int	new;
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
	unsigned char	op;
	unsigned int	active : 1;
	unsigned int	live;
}					t_pc;

typedef struct 		s_player
{
	unsigned int	live_call : 1;
	unsigned int  	last_live; //new
	unsigned int 	live_counter;
	unsigned int	loser : 1;
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

typedef struct pene
{
	int x;
	int y;
	int w;
	int h;
} rectpene;

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
	SDL_Surface		*pause_surf[2];
	unsigned int	step : 1;
	unsigned int	visual : 1;
	unsigned int	fullscreen : 1;
	unsigned int	info : 1;
	unsigned int	dump : 1;
	unsigned int 	dump_cuant;
}					t_mods;

typedef struct		s_data
{
	//anadir variable para saber cuando se alcanza el cycle to die
	unsigned int	dump;
	unsigned int 	max_checks;
	unsigned int	cycle_to_die;
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
	unsigned int 	nb_pc_active;
	unsigned int 	nbr_live;
	unsigned int	turn_cycles;
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
void 				take_champions(t_data *data, char **av, const unsigned int ac);
void 				big_hexa_2_dec(char *str, int size);
void				invert_bytes(void *arr, const size_t size);
int 				init_corewar(t_data *data, int ac, char **av);
void				put_champs_to_arena(const t_data *data);
void 				free_players(t_player *player, int nb_players);
void				put_usage();
unsigned int		get_prog_size(int fd);
char 				*read_alloc_size(int fd, int size);
void				print_board(t_data *data, t_board *board);
void 				exe_players(t_data *data);
void 				exe_players_interf(t_data *data);
void 				exe_players_dump(t_data *data);
void 				check_live_count(t_data *data);
void				fill_r1(t_data *data);
unsigned char		*get_mem_board(t_board *board, const unsigned int size);
t_pc				*realloc_pc(t_pc *pc, const unsigned int nb_pc);
unsigned char		get_size_arg(const unsigned char ocp, const unsigned char n_arg, const unsigned int dir_size);
void				get_arg(const unsigned char ocp, unsigned short pos, t_board *board, t_arg *arg);
int					get_arg_value(t_board *board, t_arg *arg, t_pc *pc);
int					ft_mod(const int nb, const unsigned int mod);
void 				check_winner(t_player *players, int nb_players);
void				clean_pc_arr(t_pc *pc, const unsigned int nb_pc);


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
void		ft_ini_interface(t_sdl *Graph, t_data *data);
void		ft_ini_font(t_sdl *Graph);
void		ft_board_to_screen(t_sdl *Graph, t_board board[MEM_SIZE], t_data *data);
void		ft_pcs_to_rack(t_sdl *Graph, t_data *data, int alpha_mod);
void		ft_set_back_to_front(t_sdl *Graph, t_data *data);
void		ft_ini_information(t_data *data);
void		ft_ini_material(t_data *data, t_sdl *Graph, SDL_Surface *info_marc);
SDL_Surface	*ft_write_string(t_sdl *Graph, char *str, int pos[2], int name);
int			ft_write_number_fields(t_sdl *Graph, t_font *font, int pos[2], SDL_Surface *number);
void		ft_update_info(t_sdl *Graph, t_data *data, int cicles_pre_die);
void		ft_put_general_info(t_sdl *Graph);
void		ft_put_player_info(t_sdl *Graph, SDL_Surface *info_marc, t_data *data, int i);
SDL_Color	ft_SDL_color(int i);
Uint32		ft_MapRGBA(SDL_PixelFormat *format, int i, int alpha);
void		ft_ini_pcs(t_sdl *Graph);
void		ft_ini_images(t_data *data, t_sdl *Graph);
void		ft_ini_sprites(t_data *data, t_sdl *Graph);
void		ft_reset_health(t_data *data, t_sdl *Graph, int player);
void		ft_check_health(t_data *data, t_sdl *Graph, int player, int t);

#endif
