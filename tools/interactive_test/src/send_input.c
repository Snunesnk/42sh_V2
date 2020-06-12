#include "interactive_test.h"

int			process_stopped(t_process process)
{
	if (is_ready(process.wchan) < 0)
		return (1);
	if (kill(process.pid, 0) < 0 || access(process.process_input, F_OK))
	{
		printf("n'a pas suffit\n");
		sleep(10);
		return (1);
	}
	return (0);
}

// This function send a cmd to a process with ioctl, storing the
// input into the queue of desired process.
void		send_input(char *input, t_process process)
{
	int				i;

	i = 0;
	while (input[i])
	{
		// Wait for the process to be ready between each sent char, otherwise process's read will return more than
		// one char, causing the input to not behave properly.
		is_ready(process.wchan);
		if (ioctl(process.fd, TIOCSTI, &(input[i])) < 0)
		{
			perror("ioctl");
			exit(1);
		}
		i++;
		printf("input: %s\n", input);
		usleep(CHAR_DELAY);
	}
}
