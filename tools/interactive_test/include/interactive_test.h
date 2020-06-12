//Needed for ioctl(2) call
#include <sys/ioctl.h>
#include <termios.h>

//Needed for print functions
#include <stdio.h>
#include <stdlib.h>

//Needed for open(2)
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//Needed for usleep(3)
#include <sys/wait.h>

//Needed for strlen(3)
#include <string.h>
#include <unistd.h>

//To read dir files
#include <dirent.h>

//To test if the programm has received several pid with isdigit
#include <ctype.h>

#include "defines.h"

typedef struct	s_process
{
	int		pid; // target's pid
	int		fd; // target's fd 0
	int		group; // target's process group
	char	*process_input; // location of target's fd 0
	char	*cmdline; // content of /proc/[g_pid]/cmdline, which is how the programm was started.
	char	*wchan; // content of /proc/[g_pid]/wchan, which contains target's state, waiting for input or waiting for a cmd.
}				t_process;

extern t_process	g_target_process;
extern t_process	g_base_process;

void		send_input(char *input, t_process process);
int			ft_strequ(char *s1, char *s2);
int			is_str_digit(char *str);
int			ft_isprint(char c);
t_process	load_target_info(t_process process, char *pid);
int			process_stopped(t_process process);
char		*ft_strjoin(char *s1, char *s2);
char		*get_filename(char *path);
t_process	get_active_process(t_process process, char *cmd);
int			get_process_group(char *pid);
void		free_process(t_process *process);
int			is_ready(char *wchan);
