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

//Needed for poll(2);
#include <poll.h>
#include <signal.h>
#define _GNU_SOURCE

//To read dir files
#include <dirent.h>

//test file extension
#define TEST_EXT ".test"

//test if process is still running
#define PROCESS_STOPPED (kill(g_pid, 0) != 0 || access(g_process_input, F_OK) > 0) ? 1 : 0

//Time waiting for input to be available before sending SIGINT, in ms
#define DELAY_TIME 300

//Time bewteen write of each chars to target process, multiplied by DELAY_TIME. Final wait is in ns.
#define INPUT_DELAY 30

//Name of target process, must end with a newline to be able to re-launch it
#define PROCESS_NAME "./21sh\n"

int		g_pid;
char	*g_process_input;

static int	ft_isprint(char c)
{
	if (c >= 32 || c <= 126)
		return (1);
	return (0);
}

// This function send a cmd to a process with ioctl, storing the
// input into the queue of desired process.
static void	send_input(char *input, int fd)
{
	int				i;
	struct pollfd	fds;
	int				status;

	//init struct for poll, to wait till input in process become available
	fds.fd = fd;
	fds.events = (POLLIN);
	fds.revents = 0;

	i = 0;
	while (input[i])
	{
		if (ioctl(fd, TIOCSTI, &(input[i])) < 0)
		{
			perror("ioctl");
			exit(1);
		}
		i++;
		// Wait between each sent char, otherwise process's read will return more than
		// one char, causing the input to not behave properly.
		if (input[i + 1] && !ft_isprint(input[i + 1]))
			usleep(DELAY_TIME * INPUT_DELAY);
	}
	usleep(DELAY_TIME * INPUT_DELAY);
	if (!strchr(input, '\n'))
		return ;
	int		nb_time_tried;
	char	stop = 3;

	nb_time_tried = 0;
	//Wait for the input to become available, or timeout after 1 seconds
	//if process didn't respond in time, quit. Not great, but don't know how to make it better now.
	while ((status = poll(&fds, 1, DELAY_TIME)) <= 0)
	{
		if (strstr(input, "exit") && PROCESS_STOPPED)
			break ;
		if (status == 0 || nb_time_tried > 0)
		{
			if (ioctl(fd, TIOCSTI, &stop) < 0)
			{
				perror("ioctl");
				exit(1);
			}
			usleep(DELAY_TIME * INPUT_DELAY);
			nb_time_tried++;
		}
		if (PROCESS_STOPPED)
		{
			dprintf(2, "process quit\n");
			exit (1);
		}
		if (nb_time_tried >= 4)
			stop = 4;
	}
	if (strstr(input, "exit") && PROCESS_STOPPED)
		send_input(PROCESS_NAME, fd);
}

static void	open_and_exec_file(char *file, int fd)
{
	FILE	*fp;

	printf("\033[36mLaunch %s\033[0m\n", file);
	if (!(fp = fopen(file, "r")))
	{
		perror("fopen");
		return ;
	}

	char	line[1024];

	while (fgets(line, 1024, fp) != NULL)
		send_input(line, fd);
	printf("\033[37m[done]\033[0m\n");
	fclose(fp);
}

static int	ft_strequ(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[j] && s1[i] && s2[i])
	{
		i++;
		j++;
	}
	return (s1[i] == s2[j]);
}

static void	exec_all_tests(int fd, int pid)
{
	DIR				*dirp;
	struct dirent	*file;
	int				ext_name = strlen(TEST_EXT);
	int				name_len;

	dirp = opendir(".");
	while (file = readdir(dirp))
	{
		name_len = strlen(file->d_name);
		if (name_len > ext_name && ft_strequ(file->d_name + name_len - ext_name, TEST_EXT) \
					&& file->d_name[0] != '.')
		{
			open_and_exec_file(file->d_name, fd);
			if (PROCESS_STOPPED)
			{
				dprintf(2, "process quit\n");
				exit (0);
			}
		}
	}
	closedir(dirp);
}

int			main(int argc, char **argv)
{
	// Some basic verifications
	if (argc < 2)
	{
		dprintf(2, "Interactive_test: no path given.\n");
		dprintf(2, "Usage: \033[31m./a.out\033[0m \033[1;34m<process_pid>\033[0m "\
				"[cmd1, cmd2, ...]\n");
		dprintf(2, "You can get the pid with \033[1;37mpidof <process>\033[0m."\
				"See you soon\n");
		return (1);
	}

	int		fd;

	if (!(g_process_input = (char *)malloc(sizeof(char) * (strlen("/proc//fd/0") \
						+ strlen(argv[1]) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	//open input fd of desired process
	sprintf(g_process_input, "/proc/%s/fd/0", argv[1]);
	if ((fd = open(g_process_input, O_WRONLY)) < 0)
	{
		perror("open");
		return (1);
	}

	int				i = 2;
	int				status;

	g_pid = atoi(argv[1]);
	// If the user send command through cmd line, execute them.
	if (argc > 2)
	{
		while (argv[i])
		{
			open_and_exec_file(argv[i], fd);
			if (PROCESS_STOPPED)
			{
				dprintf(2, "process quit\n");
				exit (0);
			}
			i++;
		}
	}
	// else exec all *.test in current directory
	else
		exec_all_tests(fd, g_pid);
	free(g_process_input);
	close(fd);
}
