/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:18:01 by efischer          #+#    #+#             */
/*   Updated: 2019/12/18 16:13:10 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# include "libft.h"
# include "job_control.h"
# include "vctlib.h"
# include "ft_getopt.h"
# include "error.h"
# include "path.h"
# include "builtins.h"

# define FAILURE EXIT_FAILURE
# define SUCCESS EXIT_SUCCESS

# define BUF_SIZE	32
# define NB_TOKEN	19
# define NB_BRACKET	2
# define TAB_END	-1 

typedef struct		s_token
{
	uint64_t		type;
	t_vector		*value;
}					t_token;

enum	e_bracket
{
	PARENTHESIS,
	WHILE_LOOP
};

enum	e_token
{
	OR_IF,
	PIPE,
	AND_IF,
	AND,
	DSEMI,
	SEMI,
	OP_PARENTHESIS,
	CL_PARENTHESIS,
	WHILE_WORD,
	DONE,
	DGREAT,
	DLESS,
	GREAT,
	LESS,
	WORD,
	IO_NB,
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
void	debug(t_list *lst);
int		get_stdin(char **line);
int		initialize_prompt_fd(void);
int		launch_all_jobs(t_list *lst);
_Bool   prompt_display(int status);
int		path_concat(char **bin);
int		get_next_token(const char *str, t_token *token);

extern int	g_retval;
extern char	g_pwd[];

#endif
