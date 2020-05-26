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

char	cmd[][999] =
{
	"ls\n",
	"slee\t 1\n",
	"exit\n",
	0
};

// This function send a cmd to a process with ioctl, storing the
// input into the queue of desired process.
static void	send_input(char *input, int fd)
{
	int			i;

	i = 0;
	while (input[i])
	{
		if (ioctl(fd, TIOCSTI, &(input[i])) < 0)
		{
			perror("ioctl 1");
			exit(1);
		}
		i++;
		// Wait between each sent char, otherwise process's read will return more than
		// one char, causing the input to not behave properly.
		usleep(100000);
	}
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
	struct pollfd	fds;

	//init struct for poll, to wait till input in process become available
	fds.fd = fd;
	fds.events = (POLLIN);
	fds.revents = 0;
	// If the user send command through cmd line, execute them.
	while (argv[i])
	{
		send_input(argv[i], fd);
		//Wait for the input to become available, or timeout after 30 seconds
		while ((status = poll(&fds, 1, 30000)) < 0);
		//if process didn't respond in time, kill the launch cmd.
		if (status == 0)
			kill(pid, SIGINT);
		i++;
	}
	i = 0;
	// Execute all cmd stored in cmd[][].
	while (i < 3)
	{
		send_input(cmd[i], fd);
		while ((status = poll(&fds, 1, 30000)) < 0);
		if (status == 0)
			kill(pid, SIGINT);
		i++;
	}
	close(fd);
}
