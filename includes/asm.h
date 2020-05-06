/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:31:05 by dberger           #+#    #+#             */
/*   Updated: 2020/05/06 22:30:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "utils.h"

# define PROG_ASM			0
# define INIT				-1
# define BITS_IN_OCTET		8
# define INFO_PROG			4
# define EMPTY				"\0"
# define MAX_ARGS			3
# define ALT_COMMENT_CHAR   ';'
# define ARG				0
# define SEP				1
# define INDX				2
# define SPACE				1
# define COMM				2
# define SPACE_COMM			3

/*
** Messages d'erreur
*/

# define CREATE_FAIL		"Can't create the file"
# define COMMAND_TWICE		"Can't have twice the same command"
# define END_INPUT			"Syntax error - unexpected end of input"
# define INVALID_COMMAND	"Invalid command"
# define INCOMPLETE			"Incomplete Header"
# define LABEL_ALLOC		"Memory allocation failure for a label"
# define LABEL_ERROR		"Lexical error for a label"
# define LEXICAL_ERROR		"Lexical Error for"
# define MALLOC_COMMENT		"Can't allocate champion's comment"
# define MALLOC_FAIL		"Memory allocation failure"
# define MALLOC_NAME		"Can't allocate champion's name"
# define MISSING_ARG		"Missing arguments for the op_code"
# define MISSING_CODE		"Missing exec_code for this champion"
# define MISSING_QUOTE		"Missing quote in header"
# define MISSING_SEP		"Missing separator_char before the argument"
# define NO_ARGS			"No arguments"
# define OPEN_FAIL			"A problem occured while opening the file"
# define SYNTAXE_ERROR		"Syntaxe Error in header"
# define TOO_BIG			"Programm exceeding the Maximum size"
# define TOO_LONG_COM		"Command [.comment] too long"
# define TOO_LONG_NAME		"Command [.name] too long"
# define TOO_MANY_ARGS		"Too many arguments for the op_code"
# define TOO_MANY_SEP_A		"Too many separator_char after the argument"
# define TOO_MANY_SEP_B		"Too many separator_char before the argument"
# define TOO_MUCH_ARGS		"Too many arguments"
# define WRONG_FORMAT		"Wrong format after .command in header"
# define WRONG_HEADER		"Wrong instruction in header"
# define WRONG_LABEL		"The following label doesn't exist"
# define WRONG_SOURCE		"Wrong source file format"
# define WRONG_REG_NUM		"A register number should be between 1 and 16"
# define WRONG_TYPE_ARG		"Wrong type of argument for the op_code"
# define WRONG_SYNTAX_OP	"Wrong syntaxe for the op_code"

/*
** Structure qui contiendra la ligne lue dans get_next_line, le numero
** de la ligne [l], ainsi que la colonne [i]: permet pour chaque message
** d'erreur d'afficher son emplacement.
*/

typedef	struct				s_s
{
	char					*line;
	int						l;
	int						i;
	t_fd					*gnl;
}							t_s;

/*
** Permet d'afficher le ou les characteres qui comportent une erreur.
** [line] et [col] indiquent ou demarrent le token,
** [end] ou il se termine, et s'il s'agit d'un argument,
** [op_type] nous permet d'afficher a quel op_code il appartient.
*/

typedef struct				s_token
{
	char					*name;
	int						line;
	int						col;
	int						end;
	int						op_type;
}							t_token;

/*
** S_argz contient les infos d'un argument d'un op_code.
** [type] : indique si c'est un registre, un direct, ou un indirect.
** [code] : permet de calculer l'encoding byte d'un op_code,
** il vaut 01 pour T_REG, 10 pour T_DIR et 11 pour T_IND.
** [lab] : contient une chaine de caractere si la valeur de l'argument
** est un label, sinon == NULL.
** [value] : contient la valeur numerique d'un argument s'il ne s'agit
** pas d'un label.
** [oct] : Nombres d'octets pris en memoire en fonction du type de
** l'argument et de l'op_code.
** [line][col]: Garde en memoire l'emplacement de l'argument en cas d'erreur
*/

typedef struct				s_argz
{
	int						type;
	int						code;
	char					*lab;
	long					value;
	size_t					oct;
	int						line;
	int						col;
}							t_argz;

/*
** S_instruct contient les infos sur chaque op_code.
** [type] : 0x01 si il s'agit de "live" par exemple
** [oct] : numero de l'octet ou est ecrit cet op_code (utile pour les labels)
** [nb_args] : nombres d'arguments necessaires pour cet op_code
** [argz[MAX_ARGS]] : tableau pouvant contenir jusqu'a 3 t_argz
** [next] : permet de creer une liste chainee d'op_code contenue dans stack
*/

typedef	struct				s_instruct
{
	size_t					type;
	size_t					oct;
	size_t					nb_args;
	t_argz					argz[MAX_ARGS];
	struct s_instruct		*next;
}							t_instruct;

/*
** S_label est une liste chainee de label avec [name] comme nom et
** [oct] pour emplacement.
*/

typedef struct				s_label
{
	char					*name;
	size_t					oct;
	struct s_label			*next;
}							t_label;

/*
** S_stack contient les infos necessaires au parsing: (avant l'ecriture)
** [champion_name] et [comment] pour le header,
** [cur_octet] : nombre d'octets utilises lorsque l'on remplit le contenu
** du fichier .cor -> utile pour les calculer l'emplacement des labels
** [first_op] et [op_list] : liste chainee d'op_code
** [first_label] et [label_list] : liste chainee de labels
*/

typedef	struct				s_stack
{
	char					*champion_name;
	char					*comment;
	int						cur_octet;
	t_instruct				*first_op;
	t_instruct				*op_list;
	t_label					*first_label;
	t_label					*label_list;
}							t_stack;

/*
** Le fichier .cor : dans [fd] son file_descriptor
** [name] : son nom - c-a-d celui du fichier .s mais avec .cor a la fin
** [content] : son contenu, qui se remplit au fur et a mesure
** [total_size] : un peu equivalent au cur_octet de s_stack:
** on l'incremente des que l'on ajoute du contenu
** [prog_size] : octet ou doit s'ecrire [total_size] dans le header
*/

typedef	struct				s_file
{
	int						fd;
	char					*name;
	char					*content;
	int						total_size;
	int						prog_size;
}							t_file;

int							gnl(int fd, char **line, t_s *s);
int							cor_file(char *source_file, t_file *out_file,
							int fd);
int							header_content(t_stack *stack, int fd,
							t_s *s);
int							get_command_type(int fd, t_s *s, int *type,
							t_token *token);
int							fill_name_com(int type, char *tmp, t_stack *stack,
							t_token *token);
int							parsing_exec(t_stack *stack, int fd, t_s *s);
int							parsing_args(t_s *s, t_instruct *op);

/*
** parsing_utils
*/

int							check_value(t_argz argz, int k, t_token *token,
							t_token *last_token);
int							check_sep(int *info, t_token *token);
int							diff(char c, int mode);
int							find_opcode(char *string);
int							find_label(t_argz argz, t_label *label);

/*
** token_utils
*/

void						*save_token(t_token *token, t_token *last_token,
							char *str_op, t_s *s);
void						init_token(t_token *token);
int							fill_token(t_s *s, int op_type, t_token *token);

/*
** op_utils
*/

int							encoding_byte(t_instruct *op);
int							ft_atolong(t_s *s, t_argz *argz);
void						update_oct(t_instruct *op, int *cur_octet, t_s *s);
t_instruct					*is_op(t_s *s, t_stack *stack, t_token *token);

/*
** arg_utils
*/

void						is_register(t_argz *argz);
void						is_direct(t_argz *argz, size_t inst_type);
void						is_indirect(t_argz *argz);
void						*argz_is_label(t_s *s, t_argz *argz,
							t_token *token);
void						*is_argument(t_s *s, size_t inst_type, t_argz *argz,
							int *sep_char);

/*
** writing_utils
*/

void						write_in_file(t_file *out_file, int indx, int n);
void						copy_string(char *dest, char *src, int size,
							int *indx);
long						count_bits(long nb);
int							nb_to_binary(t_file *out_file, int octets, int indx,
							long nb);
int							write_op_values(t_file *out_file, int *i,
							t_instruct *op, t_stack stack);

/*
** asm_free
*/

void						*free_label(t_label *label);
void						*free_op(t_instruct *op);
void						*free_op_lab(t_stack *stack);
void						*token_free(char *str, t_token *token);
void						*just_free(void *to_free1, void *to_free2);

#endif
