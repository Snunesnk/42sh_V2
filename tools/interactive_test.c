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

// This function send a cmd to a process with ioctl, storing the
// input into the queue of desired process.
static void	send_input(char *input, int fd)
{
	int				i;
	struct pollfd	fds;
	int				status;
	char			stop = 3;

	//init struct for poll, to wait till input in process become available
	fds.fd = fd;
	fds.events = (POLLIN);
	fds.revents = 0;

	printf("input: |%s|\n", input);
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
		usleep(1000);
	}
	usleep(1000);
	//Wait for the input to become available, or timeout after 3 seconds
	//if process didn't respond in time, quit. Not great, but don't know how to make it better now.
	if (!strchr(input, '\n'))
		return ;
	while ((status = poll(&fds, 1, 3000)) <= 0)
	{
		if (status == 0)
		{
			if (ioctl(fd, TIOCSTI, &stop) < 0)
			{
				perror("ioctl");
				exit(1);
			}
			usleep(1000);
			break ;
		}
	}
}

static void	open_and_exec_file(char *file, int fd)
{
	FILE	*fp;

	if (!(fp = fopen(file, "r")))
	{
		perror("fopen");
		return ;
	}

	char	line[1024];

	while (fgets(line, 1023, fp) != NULL)
		send_input(line, fd);
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

static void	exec_all_tests(int fd)
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
			open_and_exec_file(file->d_name, fd);
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

	char	*process_input;
	int		fd;

	if (!(process_input = (char *)malloc(sizeof(char) * (strlen("/proc//fd/0") \
						+ strlen(argv[1]) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	//open input fd of desired process
	sprintf(process_input, "/proc/%s/fd/0", argv[1]);
	if ((fd = open(process_input, O_WRONLY)) < 0)
	{
		perror("open");
		return (1);
	}
	free(process_input);

	int				pid = atoi(argv[1]);
	int				i = 2;
	int				status;
	// If the user send command through cmd line, execute them.
	if (argc > 2)
	{
		while (argv[i])
		{
			open_and_exec_file(argv[i], fd);
			i++;
		}
	}
	// else exec all *.test in current directory
	else
		exec_all_tests(fd);
	close(fd);
}
