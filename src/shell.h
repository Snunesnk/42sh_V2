/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:18:01 by efischer          #+#    #+#             */
/*   Updated: 2020/03/09 14:23:53 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"
# include "vctlib.h"
# include "ft_getopt.h"
# include "error.h"
# include "ft_errno.h"

# ifndef WAIT_ANY
#  define WAIT_ANY -1
# endif

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# ifndef HASH_SIZE
#  define HASH_SIZE 64
# endif

/* Flags of instruction type of redirection */
# define IOTYPE  0xF		/* type: bits 0:3 */
# define IOREAD  0x1		/* < */
# define IOWRITE 0x2		/* > */
# define IORDWR  0x4		/* <>: todo */
# define IOHERE  0x8		/* << (here file) */
# define IOCAT   0x10		/* >> */
# define IODUP   0x20		/* <&/>& */

/* Flags for complex redirection */
# define FILENAME  0x1
# define DEST      0x2
# define HEREWORD  0x4
# define FDCLOSE   0x8
# define NOFORK    0x10
# define REDSUC    0x20

char	*short_logical_path(char **cwd);
char	*short_physical_path(char **cwd);

extern char		g_pwd[PATH_MAX];
extern t_list	*g_env;

struct	s_shell_fds
{
	int					fd;
	struct s_shell_fds	*next;
};

/* Union containing Descriptor or filename */
typedef union
{
	int		dest;         /* Place to redirect to or .... */
	char	*filename;    /* filename to redirect to or ... */
	char	*hereword;    /* here-doc content used as input. */
}			t_redirectee;

/* A redirection structure for process redirections */
/* Structure describing a redirection */
struct	s_redirection
{
	struct s_redirection	*next;         /* next redirection or NULL */
	t_redirectee			redirector;    /* descriptor or varname to be redirected cf man dup2() */
	int						instruction;   /* what to do with the information, i.e. redirection type */
	int						flags;         /* additional information for complex redirections */
	int						error;         /* error type during redirection, error.c */
	t_redirectee			redirectee;    /* file descriptor or filename */
	char					*here_doc_eof; /* the word that appeared in <<eof */
	int						save[2];       /* saved fd for redir undo */
};

/* A process is a single process.  */
struct s_process
{
	struct s_process		*next;       /* next process in pipeline */
	char					**argv;      /* for exec */
	int						argc;        /* for expansions substitution */
	pid_t					pid;         /* process ID, given at fork time in job.c,
	      					uses waitpid (waitpid is not called when & at end of job) */
	char					completed;   /* true if process has completed */
	char					stopped;     /* true if process has stopped */
	int						status;      /* reported status value */
	struct s_redirection	*redir;      /* all recirections to be applied */
};

/* A job is a pipeline of processes.  */
struct s_job
{
	struct s_job		*next;          /* next active job */
	char				*command;       /* command line, used for messages */
	struct s_process	*first_process; /* list of processes in this job */
	pid_t				pgid;           /* process group ID */
	char				notified;       /* true if user told about stopped job */
	struct termios		tmodes;         /* saved terminal modes */
	int					stdin;          /* standard i/o channels */
	int					stdout;         /* standard i/o channels */
	int					stderr;         /* standard i/o channels */
};

/* Hash table structure*/
struct s_hash_table
{
	struct s_hash_table	*next; /* To avoid collision*/
	char				*command_name; /*Name of the command stored*/
	char				*command_path; /*Path of the command stored*/
	int					nb_called; /* Number of time this command has been called*/
};


typedef struct s_shell_fds		t_shell_fds;
typedef struct s_process		t_process;
typedef struct s_job			t_job;
typedef struct s_redirection	t_redirection;
typedef struct s_hash_table		t_hash_table;

int				add_to_hash_table(char *pathname, char *command_name, int nb);
int				add_name_hash_table(char *command_name, int nb);
int				check_hash_table(char *command_name);
int				ft_hash(char *to_hash);
t_hash_table	*new_hash_entry(char *pathname, char *command_name, int nb);
t_hash_table	*find_occurence(char *name);
t_hash_table	*find_prev_occurence(char *name);
void			free_hash_table(void);

extern int		g_subshell;

extern t_hash_table	**g_hash_table;

/* The active jobs are linked into a list. This is its head. */
extern t_job			*first_job;
extern pid_t			shell_pgid;
extern struct termios	shell_tmodes;
extern int				shell_terminal;
extern int				shell_is_interactive;

int		init_shell(void);
int		launch_job(t_job *j, int foreground);
void	format_job_info (t_job *j, const char *status);
void	wait_for_job(t_job *j);
void    continue_job(t_job *j, int foreground);
void    free_job(t_job *j);
int		launch_process(t_process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground);
void	free_process(t_process *p);
int     execute_process(char **argv, char **envp);
void	put_job_in_foreground(t_job *j, int cont);
void    put_job_in_background(t_job *j, int cont);
void    update_status(void);
void    do_job_notification(void);
int     get_exit_value(int status);
int     get_job_status(t_job *j, int foreground);
void    add_job_to_queue(t_job *j);
void    init_shell_sset(void);
void    restore_procmask(void);
int		job_is_stopped(t_job *j);
int     job_is_completed(t_job *j);
void    put_job_in_foreground(t_job *j, int cont);
t_job   *find_job(pid_t pgid);

extern sigset_t			g_save_procmask;

int				launch_builtin(t_process *p);
int				has_redirections(int type);
int				is_redir_type(int type);
t_redirection	*build_redirections(t_list **lst);
int				get_tokentype(t_list *lst);
char			*get_tokvalue(t_list *lst);
int				do_redirection(t_redirection *r);
int				undo_redirection(t_redirection *r);
t_redirection   *set_redirection(t_list **lst, int io_nb);

extern char	*g_filename_redir_error;

# define TRUE		1
# define FALSE		0

# define BUF_SIZE	32

# define NB_TOKEN	20

# define SET		0x01
# define EXPORT		0x02
# define RDONLY		0x04
# define ARRAY		0x08

enum	e_token
{
	SEMI,
	OR_IF,
	PIPE,
	AND_IF,
	GREATAND,
	LESSAND,
	ANDGREAT,
	AND,
	DGREAT,
	DLESSDASH,
	DLESS,
	GREAT,
	LESS,
	NEWLINE,
	IO_NB,
	COMMENT,
	WORD,
	START,
	END,
	NONE
};

typedef struct		s_token
{
	enum e_token	type;
	char			*value;
}					t_token;

typedef struct	s_ast
{
	enum e_token	type;
	t_list			*content;
	void			*left;
	void			*right;
}				t_ast;

typedef struct	s_shell_var
{
	char		*name;
	char		*value;
	uint64_t	flag;
}				t_shell_var;

void	alpha_sort(t_list **lst1, t_list **lst2, t_list **head);
void	ast_order(t_ast **ast);
void	astdel(t_ast **ast);
int		build_ast(t_ast **ast, t_list *lst);
void	debug(t_list *lst);
void	debug_ast(t_ast *ast);
void    del(void *content, size_t content_size);
void	del_env(void *content, size_t content_size);
int		execute_job(t_list *lst, int foreground);
int		execute_node(t_ast *node, int foreground);
int     ft_atoifd(const char *str);
void	ft_free_tab(int ac, char **av);
int		ft_ismeta(int c);
char	*ft_join_free(char *s1, char *s2, int op);
void	ft_merge_sort(t_list **lst, void sort(t_list**, t_list**, t_list**));
void	ft_sort_name(t_list **lst1, t_list **lst2, t_list **head);
int		get_env_list(char **environ);
char	**get_env_tab(void);
int		get_next_token(const char *str, t_token *token, enum e_token *last_token_type);
t_list	*get_shell_var(char *name);
int		get_stdin(char **line);
int		initialize_prompt_fd(void);
int		lexer(char* str, t_list **lst);
int		only_assignments(t_process *p);
int		parser(t_list *lst);
int		path_concat(char **bin);
void	print_env(t_list *env, t_list **elem);
_Bool   prompt_display(int status);
int    	set_minimal_env(void);
int		treat_shell_variables(t_process *p, int	opt);
int		treat_single_exp(char **str, int tilde);
int		treat_expansions(int argc, char **argv);

extern int	g_retval;

struct	s_tags
{
	char	*opentag;
	int		(*f)(size_t*, char**, const char*, const char*);
	char	*closetag;
};

struct	s_param
{
	char	*pname;
	char	*(*g)(const char*);
};

int		getenv_content(char **content, char *str, const char *closetag);
size_t	ft_varlen(const char *s, const char *closetag);
int		is_a_valid_chr(const char c);
int		is_valid_param(const char *str);
int		parameter_expansions(size_t *index, char **str,
			const char *opentag, const char *closetag);
int		tilde_expansion(size_t *index, char **str,
			const char *opentag, const char *closetag);

#endif
