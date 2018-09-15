#ifndef LIBASM_H
# define LIBASM_H
# include "../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>
#define	HASH_SIZE 100
#define	REG_ASM_SIZE 1

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct	s_header
{
	char	*prog_name;
	char	*comment;
	int	name_size;
	int	comment_size;
	char	*name_line;
	char	*comment_line;
	int	line_n;
}		t_header;

typedef struct	s_label
{
	char	*name;	//$
	int	id;	//$
	int	pos;	//falta!!!!
	struct s_label	*copy;	//$
	struct s_label	*actual;	//$
	struct s_label	*next;	//$
}		t_label;

typedef	struct	s_line
{
	int		order_n;
	int		arg[3];
	char		*arg_lab[3];
	char		arg_size[3];
	unsigned char		ocp;
	char		*line;
	int		pos;   //sin peso
	int		w;	//weight
	t_label		*label;
	struct s_line	*next;
}		t_line;

typedef struct	ord
{
	t_line *bgn;
	t_label **label;
}		t_ord;

//SRCS
int     assembler(int fd, char *filename);

//FUNC
t_header	ft_getname(char *line, int n_line, t_header h);
int     ft_strcmp_index(char *s1, char *s2);
int     ft_strcmp_index_jmp(char *s1, char *s2);
int ft_strcmp_to(char *s1, char *s2);
t_label	*ft_newlabel(char *name, int id);
t_line	*ft_newline(t_label *l, int ord_n, char *line, int w);
t_line          *ft_getorders(char *l, t_label **label, int j, int n_line);
t_label         **ft_add_new_label(t_label **label, int  id, char *l, int i);
t_line  *ft_add_new_line(char *l, int cnt, int i, int n_line);
int             ft_atoi_asm(const char *str, int pos, int *val);
int     ft_jmp_s_t(char *s, int i);
int     ft_hash_it(int id, int max);
int     ft_extract_label_line(t_line *line, t_label *label, int pos);

//FUNC CONV
int     ft_extract_dir(t_line **line, int i, int n_line, int pos);
int     ft_extract_dir_2(t_line **line, int i, int n_line, int pos);
int     ft_extract_ind(t_line **line, int i, int n_line, int pos);
int     ft_extract_ind_label(t_line **line, int i, int n_line, int pos);
int     ft_extract_reg(t_line **line, int i, int n_line, int pos);

//FUNC ORDERS
t_line  *ft_add_ld(char *l, int cnt, int i, int n_line);
t_line  *ft_add_lld(char *l, int cnt, int j, int n_line);
t_line  *ft_add_or(char *l, int cnt, int j, int n_line);
t_line  *ft_add_st(char *l, int cnt, int j, int n_line);
t_line  *ft_add_add(char *l, int cnt, int j, int n_line);
t_line  *ft_add_aff(char *l, int cnt, int j, int n_line);
t_line  *ft_add_and(char *l, int cnt, int j, int n_line);
t_line  *ft_add_ldi(char *l, int cnt, int j, int n_line);
t_line  *ft_add_sub(char *l, int cnt, int j, int n_line);
t_line  *ft_add_sti(char *l, int cnt, int j, int n_line);
t_line  *ft_add_xor(char *l, int cnt, int j, int n_line);
t_line  *ft_add_lldi(char *l, int cnt, int j, int n_line);
t_line  *ft_add_fork(char *l, int cnt, int j, int n_line);
t_line  *ft_add_zjmp(char *l, int cnt, int j, int n_line);
t_line  *ft_add_lfork(char *l, int cnt, int j, int n_line);
t_line  *ft_add_live(char *l, int cnt, int j, int n_line);

//ERROR
int     ft_invalidargv(int sel, char *s);
void	ft_error_getname(int n_line, int sel);
void ft_error_order(int l, int sel, char *s, char *ex);
void ft_error_par(int l, int sel, char *s, char *ex);
void ft_error_label(int l, int sel, char *s);
void    ft_check_for_coments(char *l, int i,int n_line);
void ft_error_getorders(int l, int sel);

//PRINT
void    ft_printlabel(t_label **l);
#endif
