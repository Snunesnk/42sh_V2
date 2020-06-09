/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:18:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/06/09 11:45:17 by yforeau          ###   ########.fr       */
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
# include <dirent.h>
# include <pwd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"
# include "vctlib.h"
# include "ft_getopt.h"
# include "error.h"
# include "ft_errno.h"
# include "ft_readline.h"

# ifndef WAIT_ANY
#  define WAIT_ANY -1
# endif

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# ifndef HASH_SIZE
#  define HASH_SIZE 1
# endif

# define TRUE		1
# define FALSE		0
# define ON		TRUE
# define OFF		FALSE
# define BUF_SIZE	32
# define NB_TOKEN	17

# define SET					0x010000
# define EXPORT					0x020000
# define RDONLY					0x040000
# define TEMP					0x080000

# define SHVAR_ADD_OFF			16
# define SHVAR_RM_OFF			8
# define SHVAR_OVERWRITE_OFF	0

# define SHVAR_ADD_MASK			0x0000ff
# define SHVAR_RM_MASK			0x00ff00
# define SHVAR_OVERWRITE_MASK	0xff0000

# define IONONE		0x0
# define IOTYPE		0xF
# define IOREAD		0x1
# define IOWRITE	0x2
# define IORDWR		0x4
# define IOHERE		0x8
# define IOCAT		0x10
# define IODUP		0x20

# define FILENAME	0x1
# define DEST		0x2
# define HEREWORD	0x4
# define FDCLOSE	0x8
# define NOFORK		0x10
# define REDSUC		0x20

# define MAX_SIG	32

# define IFS					"\t \n"
# define IFS_SHELL_QUOTES		"\t \n\"\'\\"

extern char						*g_token_tab[NB_TOKEN];
char							*short_logical_path(char **cwd);
char							*short_physical_path(char **cwd);

extern t_list					*g_env;
extern t_list					*g_tmp_env;
extern t_list					*g_pending_cmd;

extern int						*g_parse_table[NB_TOKEN];

extern t_list					*g_alias;

typedef struct					s_signal
{
	int		sig;
	char	*str;
}								t_signal;

typedef struct					s_redirectee
{
	int		dest;
	char	*filename;
	char	*hereword;
}								t_redirectee;

struct							s_redirection
{
	struct s_redirection	*next;
	t_redirectee			redirector;
	int						instruction;
	int						flags;
	int						error;
	t_redirectee			redirectee;
	char					*here_doc_eof;
	int						save[2];
};

struct							s_process
{
	struct s_process		*next;
	char					**argv;
	int						argc;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						status;
	struct s_redirection	*redir;
	int						infile;
	int						outfile;
	int						errfile;
	int						assignments_count;
};

struct							s_job
{
	struct s_job		*next;
	char				*command;
	struct s_process	*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
};

struct							s_hash_table
{
	struct s_hash_table	*next;
	char				*command_name;
	char				*command_path;
	int					nb_called;
};

typedef struct s_process		t_process;
typedef struct s_job			t_job;
typedef struct s_redirection	t_redirection;
typedef struct s_hash_table		t_hash_table;

int								add_to_hash_table(char *pathname, \
		char *command_name, int nb);
int								add_name_hash_table(char *command_name, int nb);
int								check_hash_table(char *command_name);
int								ft_hash(char *to_hash);
t_hash_table					*new_hash_entry(char *pathname, \
		char *command_name, int nb);
t_hash_table					*find_occurence(char *name);
t_hash_table					*find_prev_occurence(char *name);
void							free_hash_table(void);

extern int						g_job_control_enabled;
extern int						g_noexit;
extern int						g_last_exit;
extern int						g_force_exit;
extern int						g_interrupt_immediately;
extern int						g_oneline;
extern int						g_trap;

extern t_hash_table				*(g_hash_table[HASH_SIZE]);

extern t_job					*g_first_job;
extern pid_t					g_shell_pgid;
extern struct termios			shell_tmodes;
extern int						g_shell_terminal;
extern int						g_shell_is_interactive;

int								get_stdin(int fd, char **line);
char							*get_input_fd(int fd, int close_quotes, \
		char *prompt);
int								exec_input(char *input, int fd);
int								init_shell(char *argv, int argc);
int								launch_job(t_job *j, int foreground);
void							free_all_processes(t_process *p);
void							free_job(t_job *j);
void							free_all_jobs(void);
void							free_a_job(t_job *j);
void							format_job_info (t_job *j, const char *status);
void							wait_for_job(t_job *j);
void							continue_job(t_job *j, int foreground);
int								launch_process(t_process *p, pid_t pgid, \
		int foreground);
void							free_lst(t_list *lst);
void							free_process(t_process *p);
int								execute_process(char **argv, char **envp, \
		t_hash_table *tmp, char *pathname);
void							put_job_in_foreground(t_job *j, int cont);
void							put_job_in_background(t_job *j, int cont);
void							update_status(void);
void							do_job_notification(t_job *j, t_job *jlast, \
		t_job *jnext);
int								get_exit_value(int status);
int								get_job_status(t_job *j, int foreground);
void							add_job_to_queue(t_job *j);
void							init_shell_sset(void);
void							restore_procmask(void);
const char						*strsig(int sig);
int								job_is_stopped(t_job *j);
int								are_stopped_jobs(void);
int								job_is_completed(t_job *j);
void							put_job_in_foreground(t_job *j, int cont);
t_job							*find_job(pid_t pgid);
void							display_sigmsg(int sig);
void							display_sigmsg2(int sig);

extern sigset_t					g_save_procmask;

int								launch_builtin(t_process *p);
int								has_redirections(int type);
int								fd_need_be_open(t_redirection *r);
int								is_redir_type(int type);
t_redirection					*build_redirections(t_list **lst);
int								get_tokentype(t_list *lst);
char							*get_tokvalue(t_list *lst);
int								do_redirection(t_redirection *r);
t_redirection					*set_redirection(t_list **lst, int io_nb);
char							*dup_token_value(char **argv, int i, \
		t_list *lst);
char							**dup_tok_argv(t_list *lst, int argc, \
		char **argv);
void							free_redirections(t_redirection *r);
int								undo_redirection(t_redirection *r);
void							free_redirections(t_redirection *r);
int								undo_iowrite(t_redirection *r);
int								undo_ioread(t_redirection *r);
int								undo_iodup(t_redirection *r);
int								undo_iodfile(t_redirection *r);
int								undo_redirection_internal(t_redirection *r);

int								has_redirections(int type);
int								ha(char *str);
int								dupit(int fd, t_redirection *r);
t_redirection					*set_redirection(t_list **lst, int io_nb);
t_redirection					*type_less_redirection(t_list **lst, int io_nb);
t_redirection					*type_dless_redirection(t_list **lst, \
		int io_nb);
t_redirection					*type_lessand_redirection(t_list **lst, \
		int io_nb);
t_redirection					*subtype_great_redirection(t_list **lst, \
		int io_nb);
t_redirection					*type_great_redirection(t_list **lst, \
		int io_nb);
t_redirection					*type_dgreat_redirection(t_list **lst,\
		int io_nb);
t_redirection					*type_greatand_redirection(t_list **lst, \
		int io_nb);
t_redirection					*type_andgreat_redirection(t_list **lst, \
		int io_nb);

int								valid_fd(char *s, int fd, int open);
int								check_if_directory(char *filename);
int								do_iowrite(t_redirection *r, \
		t_redirection *beg);
int								do_iocat(t_redirection *r, \
		t_redirection *beg);
int								do_ioread(t_redirection *r, \
		t_redirection *beg);
int								do_iohere(t_redirection *r, \
		t_redirection *beg);
int								do_iodfile(t_redirection *r, \
		t_redirection *beg);
int								do_iodread(t_redirection *r, \
		t_redirection *beg);
int								do_iodup(t_redirection *r, \
		t_redirection *beg);
int								do_redirection(t_redirection *r);

extern char						*g_filename_redir_error;
extern char						*g_tokval[NB_TOKEN];

enum							e_token
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
	WORD,
	NONE
};

typedef struct					s_token
{
	enum e_token	type;
	char			*value;
	int				expand_heredoc;
}								t_token;

typedef struct					s_ast
{
	int				type;
	t_list			*content;
	struct s_ast	*left;
	struct s_ast	*right;
}								t_ast;

typedef struct					s_shell_var
{
	char		*name;
	char		*value;
	uint64_t	flag;
}								t_shell_var;

void							alpha_sort(t_list **lst1, t_list **lst2, \
		t_list **head);
void							free_token(t_token *token);
void							free_lst(t_list *lst);
void							free_ast(t_ast *ast);
t_ast							*build_ast(t_list **lst);
t_ast							*alloc_node(int type, t_list *pipeline, \
		t_ast *left, t_ast *right);
void							debug(t_list *lst);
void							debug_ast(t_ast *ast);
void							del(void *content, size_t content_size);
void							del_elem(void *content, size_t content_size);
void							del_env(void *content, size_t content_size);
int								execute_job(t_list *lst, int foreground);
int								mark_process_status(pid_t pid, int status);
int								execute_node(t_ast *node, int foreground);
int								ft_atoifd(const char *str);
int								ft_ismeta(int c);
char							*ft_join_free(char *s1, char *s2, int op);
char							*commandline(t_list *lst);
void							get_job_command(t_ast *ast, char **command);
void							ft_merge_sort(t_list **lst, \
		void sort(t_list**, t_list**, t_list**));
void							ft_sort_name(t_list **lst1, t_list **lst2, \
		t_list **head);
int								get_env_list(char **environ);
char							**get_env_tab(void);
int								is_new_path(void);
int								name_shvar_cmp(void *str_ref, void *shvar_ptr);
void							print_shell_var(t_list *svar_lst,
		int (*pshvarf)(t_shell_var *svar));
char							*get_shell_var(const char *name,
		t_list *svar_lst);
int								unset_shell_var(const char *name,
		t_list **svar_lst);
int								flag_shell_var(const char *name, uint64_t flags,
		t_list *svar_lst);
int								set_shell_var(const char *name,
		const char *value, uint64_t flags, t_list **svar_lst);
t_token							*get_word(const char *str, size_t *i, \
		int prevtype);
int								initialize_prompt_fd(void);
t_list							*lexer(const char *str);
t_list							*list_tokens(const char *input);
int								subprompt(int fd, t_list **lst, int qmode);
char							*heredoc(int fd, char **eof, int *qmode);
int								check_alias(t_list **lst, int check);
int								is_valid_identifier(const char *str,
		const char *stop);
char							*is_valid_assignment(const char *str);
int								get_assignment(const char *assignment,
									char **name, char **value);

int								parser(t_list *lst, int fd);
int								main_error(int status, t_list *lst);
int								path_concat(char **bin, char *beg, char *env, \
		char *dir);
void							print_env(t_list *env, t_list **elem);
_Bool							prompt_display(int status);
int								set_minimal_env(void);
int								treat_shell_variables(t_process *p,
		uint64_t flags);
void							unset_temp_shell_variables(void);
void							set_temp_shell_variables(void);
int								treat_single_exp(char **str,
	int tilde, char *equal);
int								expand_heredoc(char **hereword);
int								treat_expansions(t_process *p);
char							*get_user_home(char *start, char *end);
int								expand_filename(t_redirection *r, char **word);

int								execute_pipeline(t_ast *node, int foreground);
int								execute_semi(t_ast *node, int foreground);
int								execute_subshell(t_ast *node, int foreground);
int								execute_and(t_ast *node, int foreground);
int								execute_andand(t_ast *node, int foreground);
int								execute_or(t_ast *node, int foreground);
int								execute_node(t_ast *node, int foreground);
int								get_argc(t_list *lst, int argc, t_token *t);
int								is_redir_type(int type);
char							*get_tokvalue(t_list *lst);
int								get_tokentype(t_list *lst);

extern int						g_retval;

struct							s_tags
{
	char	*opentag;
	int		(*f)(size_t*, char**, const char*, const char*);
	char	*closetag;
};

extern const struct s_tags		g_tags[];

struct							s_param
{
	char	*pname;
	char	*(*g)(const char*);
};

int								getenv_content(char **content, char *str, \
		const char *closetag);
size_t							ft_varlen(const char *s, const char *closetag);
int								is_a_valid_chr(const char c);
int								is_valid_param(const char *str);
int								dollar_expansions(size_t *lcontent, \
		char **str, const char *opentag, const char *closetag);
int								parameter_expansions(size_t *lcontent, \
		char **str, const char *opentag, const char *closetag);
int								tilde_expansion(size_t *index, char **str, \
		const char *opentag, const char *closetag);
int								pathname_expansion(t_process *p, int i, \
		int *skip);
int								replace_fields(t_process *p, int i,
		char **av, int ac);
int								field_split(t_process *p, int i, int *fields);
void							load_config(void);
int								is_valid_redir(t_list *lst);

struct							s_param_exp
{
	int		ret;
	size_t	lopen;
	size_t	lvarname;
	size_t	lclose;
	char	*rest;
	size_t	lrest;
	char	*content;
	size_t	lcontent;
	char	*new;
};

int								exit_clean(int status);

/*
** Functions needed by builtin env
** TODO: delete builtin env, make functions static again, and delete
** these prototyes
*/
int								check_type(char *pathname,
		int is_env);
int								builtin_keyword_exec(char **argv);
int								process_execve(char **argv,
		char **envp, char *pathname);

/*
** Debug functions
*/
void							graph_ast(t_ast *ast);

#endif
