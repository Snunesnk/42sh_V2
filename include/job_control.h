#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <sys/types.h>
# include <termios.h>

/* A process is a single process.  */
struct s_process
{
  struct s_process	*next;       /* next process in pipeline */
  char			**argv;      /* for exec */
  pid_t			pid;         /* process ID, given at fork time in job.c,
						uses waitpid (waitpid is not called when & at end of job) */
  char			completed;   /* true if process has completed */
  char			stopped;     /* true if process has stopped */
  int			status;      /* reported status value */
  int			infile;      /* standard i/o channels for proc */
  int			outfile;     /* standard i/o channels for proc */
  int			errfile;     /* standard i/o channels for proc */
};

/* A job is a pipeline of processes.  */
struct s_job
{
  struct s_job		*next;          /* next active job */
  char			*command;       /* command line, used for messages */
  struct s_process	*first_process; /* list of processes in this job */
  pid_t			pgid;           /* process group ID */
  char			notified;       /* true if user told about stopped job */
  struct termios	tmodes;         /* saved terminal modes */
  int			stdin;          /* standard i/o channels */
  int			stdout;         /* standard i/o channels */
  int			stderr;         /* standard i/o channels */
};

typedef struct s_process	t_process;
typedef struct s_job		t_job;

/* The active jobs are linked into a list. This is its head. */
extern t_job		*first_job;
extern pid_t		shell_pgid;
extern struct termios	shell_tmodes;
extern int		shell_terminal;
extern int		shell_is_interactive;

int	init_shell(void);
void	launch_job(t_job *j, int foreground);
void	format_job_info (t_job *j, const char *status);
void	wait_for_job(t_job *j);
void    continue_job(t_job *j, int foreground);
void    free_job(t_job *j);
int	launch_process(t_process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground);
void	free_process(t_process *p);
/*int	execp(char **agrv, char **environ);
*/
int     launch_builtin(t_process *p);

#endif
