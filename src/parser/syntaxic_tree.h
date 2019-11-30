#ifndef SYNTAXIC_TREE_H
# define SYNTAXIC_TREE_H

# include <sys/types.h>
# include <termios.h>

/*
**  Reference of the following:
**  https://www.gnu.org/software/libc/manual/html_node/Data-Structures.html#Data-Structures
*/

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
};

/* A job is a pipeline (a singly-linked list or FIFO, refers to ft_queue methods) of processes.  */
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

struct s_node
{
	int		procedure; /* some procedures will be launcher in a subshell once procedure type dected */
	struct s_job	*job; /* series of pipelines (simple_command for now) to execute */
};

typedef struct s_process	t_process;
typedef struct s_job		t_job;
typedef struct s_node		t_node;

#endif
