/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:31:05 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 13:22:53 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "utils.h"

# define PROG_ASM		0
# define INIT			-1
# define MAX_SIZE_FILE		2875 // to delete
# define BITS_IN_OCTET		8
# define PADDING		4
# define INFO_PROG		4
# define EMPTY			"\0"
# define MAX_ARGS		3
# define ALT_COMMENT_CHAR    	';'
# define ARG_N			0
# define SEP			1
# define INDX			2

///// ERROR MESSAGE ///
# define NO_ARGS		"No arguments"
# define TOO_MUCH_ARGS		"Too many arguments"
# define OPEN_FAIL		"A problem occured while opening the file"
# define WRONG_SOURCE		"Wrong source file format"
# define MALLOC_FAIL		"Memory allocation failure"
# define MALLOC_NAME		"Can't allocate champion's name"
# define MALLOC_COMMENT		"Can't allocate champion's comment"
# define CREATE_FAIL		"Can't create the file"
# define INVALID_COMMAND	"Invalid command"
# define SYNTAXE_ERROR		"Syntaxe Error in header"
# define INCOMPLETE		"Incomplete Header"
# define WRONG_HEADER		"Wrong .command in header"
# define WRONG_FORMAT		"Wrong format after .command in header"
# define TOO_LONG_NAME		"Command [.name] too long"
# define TOO_LONG_COM		"Command [.comment] too long"
# define WRONG_REG_NUM		"A register number should be between 1 and 16"
# define WRONG_TYPE_ARG		"Wrong type of argument for the op_code"
# define MISSING_SEP		"Missing separator_char before the argument"
# define TOO_MANY_SEP_B		"Too many separator_char before the argument"
# define TOO_MANY_SEP_A		"Too many separator_char after the argument"
# define MISSING_ARG		"Missing arguments for the op_code"
# define TOO_MANY_ARGS		"Too many arguments for the op_code"
# define COMMAND_TWICE		"Can't have twice the same command"
# define WRONG_SYNTAX_OP	"Wrong syntaxe for the op_code"
# define LABEL_ERROR		"Lexical error for a label"
# define LABEL_ALLOC		"Memory allocation failure for a label"
# define MISSING_CODE		"Missing exec_code for this champion"
# define LEXICAL_ERROR		"Lexical Error for"
# define WRONG_LABEL		"The following label doesn't exist"

typedef	struct			s_s
{
	char			*line;
	int			l;
	int			i;
}				t_s;

typedef struct			s_token
{
	char			*name;
	int			line;
	int			col;
	int			end;
	int			op_type;
}				t_token;

typedef struct			s_argz
{
	int			type; // T_REG, T_DIR, T_IND
	int			code; // REG_CODE, DIR_CODE, IND_CODE
	char			*lab; // NULL sauf si appel a label (:live)
	long			value; // si lab != NULL on ne prend pas en compte value
	size_t			oct; // nombre d'octets pris en memoire en fonction du type
	int			line; // for label errors
	int			col; // for label errors
}				t_argz;

typedef struct 			s_instruct
{
	size_t			type; // 0x01 si "live" par exemple
	size_t 			oct; // numero de l'octet ou est ecrit 0x01
	size_t			nb_args; // si "sti" on sait tout de suite que c'est 3
	t_argz			argz[MAX_ARGS]; // liste chainee ou tableau de structure 
	struct s_instruct	*next;
}				t_instruct;

typedef struct 			s_label
{
	char			*name; // par exemple "l2" ou "noname1"
	size_t			oct; // place du label dans 
	struct s_label		*next; // liste chainee de label
}				t_label;

typedef struct			s_stack
{
	char			*champion_name;
	char			*comment;
	int			cur_octet; // permet de savoir ou on se trouve
	t_instruct		*first_op;
	t_instruct		*op_list;
	t_label			*first_label; // liste chainee de label
	t_label			*label_list; // liste chainee de label
}				t_stack;

typedef struct 			s_file
{
	int			fd;
	char			*name;
	char			*content;
	int			total_size;
	int			prog_size;
}				t_file;

int				cor_file(char *source_file, t_file *out_file, int fd);
int				get_header_command(t_stack *stack, int fd, t_s *s);
int				get_command_type(int fd, t_s *s, int *type, t_token *token);
int				parsing_exec(t_stack *stack, int fd, t_s *s);
/////////////////////// parsing arg   //////////////////////////
void				is_register(t_argz *argz);
void				is_direct(t_argz *argz, size_t inst_type);
void				is_indirect(t_argz *argz);
int				check_args(t_s *s, t_instruct *op);
/////////////////////// parsing utils   //////////////////////////
int				diff_com_end(char c);
int				diff_space(char c);
void				init_token(t_token *token);
int				fill_token(t_s *s, int op_type, t_token *token);
int				find_opcode(char *string);
int				find_label(t_argz argz, t_label *label);
int				encoding_byte(t_instruct *op);
int				ft_atolong(t_s *s, t_argz *argz);
void				update_oct(t_instruct *op, int *cur_octet, t_s *s);
/////////////////////// writing utils   //////////////////////////
void				write_in_file(t_file *out_file, int indx, int n);
void				copy_string(char *dest, char *src, int size, int *indx);
long				count_bits(long nb);
void				nb_to_binary(t_file *out_file, int octets, int indx, long nb);
int				write_op_values(t_file *out_file, int *i, t_instruct *op, t_stack stack);
/////////////////////// free functions ///////////////////////////
void				*token_free(char *str, t_token *token);

void				*just_free(void *to_free1, void *to_free2);
void				*free_op_lab(t_stack *stack);
void				*free_op(t_instruct *op);
void				*free_label(t_label *label);
/////////////////////// To delete   //////////////////////////
void				print_tester(t_stack *stack);

#endif
