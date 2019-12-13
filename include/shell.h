#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <stdint.h>
# include "libft.h"
# include "job_control.h"

# define FAILURE EXIT_FAILURE
# define SUCCESS EXIT_SUCCESS

# define BUF_SIZE	32
# define NB_TOKEN	15
# define NB_BRACKET	2
# define TAB_END	-1 

typedef struct		s_token
{
	uint64_t		type;
	char			*value;
}					t_token;

enum	e_bracket
{
	PARENTHESIS,
	WHILE_LOOP
};

enum	e_token
{
	PIPE,
	AND,
	SEMICOLON,
	OP_PARENTHESIS,
	CL_PARENTHESIS,
	WHILE_WORD,
	DONE,
	R_DB_REDIR,
	L_DB_REDIR,
	R_REDIR,
	L_REDIR,
	WORD,
	COMMENT,
	START,
	END
};

typedef struct	s_bracket
{
	uint64_t	open;
	uint64_t	close;
}				t_bracket;

int		lexer(const char* str, t_list **lst);
int		parser(t_list *lst, uint64_t *buffer, size_t index);
int		bracket(t_list *lst, uint64_t *buffer, size_t index);
void		debug(t_list *lst);

#endif
