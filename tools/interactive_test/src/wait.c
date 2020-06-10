#include "interactive_test.h"

static int	is_same_process(char *cmdline)
{
	FILE	*fp;
	int		status;

	status = 0;
	if (!(fp = fopen(cmdline, "r")))
	{
		perror("open in is_same_process");
		exit (1);
	}

	char	line[1024];
	char	*tmp;
	char	*input;

	input = NULL;
	bzero(line, 1024);
	while (fgets(line, 1023, fp) != NULL)
	{
		tmp = input;
		input = ft_strjoin(input, line);
		free(tmp);
		bzero(line, 1024);
	}
	fclose(fp);
	if (ft_strequ(input, g_target_process.cmdline))
		status = 1;
	free(input);
	return (status);
}

static char	*get_new_process_pid(void)
{
	DIR				*dirp;
	struct dirent	*file;
	char			line[1024];
	char			*pid;

	if (!(dirp = opendir("/proc")))
	{
		perror("opendir failed in get_new_process_pid");
		exit(1);
	}
	while ((file = readdir(dirp)))
	{
		if (file->d_name[0] == '.' || !is_str_digit(file->d_name))
			continue ;
		bzero(line, 1023);
		sprintf(line, "/proc/%s/cmdline", file->d_name);
		if (is_same_process(line))
			break ;
	}
	if (file)
		pid = strdup(file->d_name);
	else
	{
		printf("no proc found\n");
		exit (1);
	}
	closedir(dirp);
	return (pid);
}

static void	free_process(t_process *process)
{
	close(process->fd);
	free(process->process_input);
	process->process_input = NULL;
	free(process->cmdline);
	process->cmdline = NULL;
	free(process->wchan);
	process->wchan = NULL;
}

// This function "revive" the process if it was exit by "exit"
// Maybe I'm gonna add other cases where it is acceptable for the shell to quit
// and so revive it too.
static void	re_launch_process(void)
{
	char	*pid;

	send_input(g_target_process.cmdline, g_target_process);
	send_input("\n", g_target_process);
	usleep(INPUT_DELAY);
	pid = get_new_process_pid();
	free_process(&g_target_process);
	g_target_process = load_target_info(g_target_process, pid);
	free(pid);
}

int		is_ready(char *wchan)
{
	char	line[1024];
	int		fd;
	int		status;

	bzero(line, 1024);
	if (!(fd = open(wchan, O_RDONLY)))
	{
		perror("open in is_ready");
		exit(1);
	}
	read(fd, line, 1023);
	close(fd);
	if (ft_strequ(line, "0"))
	{
		usleep(INPUT_DELAY);
		status = is_ready(wchan);
		usleep(INPUT_DELAY);
		return (status);
	}
	if (ft_strequ(line, "wait_woken"))
		return (1);
	return (0);
}

static void	wait_for_process(t_process process)
{
	int		nb_tried;
	char	stop[2];
	int		micro_sleep;

	micro_sleep = TIMEOUT / 10;
	stop[0] = 3;
	stop[1] = 0;
	nb_tried = 0;
	while (!is_ready(process.wchan))
	{
		if (process_stopped(process))
		{
			free_process(&process);
			break ;
		}
		usleep(micro_sleep);
		nb_tried += micro_sleep;
		if (nb_tried == TIMEOUT)
			send_input(stop, process);
		if (nb_tried == 2 * TIMEOUT)
			stop[0] = 4;
		if (nb_tried == 3 * TIMEOUT)
		{
			printf("infinite loop\n");
			kill(SIGTERM, process.pid);
			nb_tried = 0;
			while (!process_stopped(process))
			{
				usleep(micro_sleep);
				nb_tried += micro_sleep;
				if (nb_tried == TIMEOUT)
				{
					kill(SIGKILL, process.pid);
					break ;
				}
			}
			exit(1);
		}
	}
}

t_process	find_active_process(void)
{
	DIR				*dirp;
	struct dirent	*file;
	t_process		process;
	char			line[1024];
	int				new_process;

	new_process = 0;
	process = g_target_process;
	if (!(dirp = opendir("/proc")))
	{
		perror("opendir failed in find_active_process");
		exit(1);
	}
	while ((file = readdir(dirp)))
	{
		if (file->d_name[0] == '.' || !is_str_digit(file->d_name))
			continue ;
		bzero(line, 1024);
		if (g_target_process.group != get_process_group(file->d_name))
			continue ;
		sprintf(line, "/proc/%s/wchan", file->d_name);
		if (is_ready(line))
		{
			new_process = 1;
			process = load_target_info(process, file->d_name);
			break ;
		}
	}
	closedir(dirp);
	if (!new_process && !is_ready(process.wchan))
	{
		wait_for_process(process);
		return (find_active_process());
	}
	return (process);
}

t_process	get_active_process(t_process process, char *cmd)
{
	if (process_stopped(g_target_process) && !strstr(cmd, "exit"))
	{
		dprintf(2, "process was killed\n");
		exit(1);
	}
	else if (process_stopped(g_target_process))
	{
		re_launch_process();
		return (g_target_process);
	}
	else if (is_ready(g_target_process.wchan))
		return (g_target_process);
	else if (is_ready(process.wchan))
		return (process);
	else if (process_stopped(process))
		free_process(&process);
	return (find_active_process());
}
