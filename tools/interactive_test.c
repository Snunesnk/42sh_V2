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
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <signal.h>
#include <poll.h>

//To read dir files
#include <dirent.h>

//To test if the programm has received several pid with isdigit
#include <ctype.h>

//test file extension
#define TEST_EXT ".test"

//test if process is still running
#define PROCESS_STOPPED (kill(g_pid, 0) != 0 || access(g_process_input, F_OK) > 0) ? 1 : 0

//Time waiting for input to be available before sending SIGINT, in ms
#define DELAY_TIME 300

//Time bewteen write of each chars to target process, multiplied by DELAY_TIME. Final wait is in ns.
#define INPUT_DELAY 30

int		g_pid = 0; // target's pid
int		g_fd = -1; // target's fd 0
char	*g_process_input = NULL; // location of target's fd 0
char	*g_cmdline = NULL; // content of /proc/[g_pid]/cmdline, which is how the programm was started.
char	g_wchan = NULL; // content of /proc/[g_pid]/wchan, which contains target's state, waiting for input or waiting for a cmd.

static void	send_input(char *input);
static int	ft_strequ(char *s1, char *s2);

static int	ft_isprint(char c)
{
	if (c >= 32 || c <= 126)
		return (1);
	return (0);
}

static int	ft_strequ(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == s2[i])
		return (1);
	return (0);
}

static void	add_to_cmdline(char *buf)
{
	char	*tmp;
	int		len;

	tmp = g_cmdline;
	len = strlen(buf);
	if (g_cmdline)
		len += strlen(g_cmdline);
	if (!(g_cmdline = malloc(sizeof(char) * (len + 1))))
	{
		perror("malloc");
		exit(1);
	}
	if (tmp)
		strcat(g_cmdline, tmp);
	strcat(g_cmdline, buf);
	free(tmp);
}

// Open desired process input
static void	load_target_info(char *pid)
{
	char	*cmdline_file;
	int		cmdline_fd;
	char	*out;
	char	tmp_buf[1024];

	if (g_process_input)
	{
		free(g_process_input);
		g_process_input = NULL;
	}
	if (g_cmdline)
	{
		free(g_cmdline);
		g_cmdline = NULL;
	}
	if (g_fd)
		close(g_fd);
	if (g_fd_one)
		close(g_fd_one);
	if (!(g_process_input = (char *)malloc(sizeof(char) * (strlen("/proc//fd/0") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	if (!(out = (char *)malloc(sizeof(char) * (strlen("/proc//fd/1") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	if (!(cmdline_file = (char *)malloc(sizeof(char) * (strlen("/proc//cmdline") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	sprintf(g_process_input, "/proc/%s/fd/0", pid);
	sprintf(out, "/proc/%s/fd/1", pid);
	sprintf(cmdline_file, "/proc/%s/cmdline", pid);
	//open input fd of desired process
	if ((g_fd = open(g_process_input, O_RDWR)) < 0)
	{
		perror("open");
		exit(1);
	}
	if ((g_fd_one = open(out, O_RDONLY)) < 0)
	{
		perror("open");
		exit(1);
	}
	free(out);
	// open cmdline file of process, to know how was it launch, to be able to launch
	// it in the exact same way
	if ((cmdline_fd = open(cmdline_file, O_RDONLY)) < 0)
	{
		perror("open");
		exit(1);
	}
	free(cmdline_file);
	bzero(tmp_buf, 1024);
	while (read(cmdline_fd, tmp_buf, 1023) > 0)
	{
		add_to_cmdline(tmp_buf);
		bzero(tmp_buf, strlen(tmp_buf));
	}
	close(cmdline_fd);
}

// This is experimental, and i'm sure it can be improved.
// For now, I'm gonna get the new pid of the revived process by looking into
// each dir of /proc for the file 'cmdline', which contains the cmdline of how
// the programm was started.
static char	*get_new_process_pid(void)
{
	return (NULL) ;
}

// This function "revive" the process if it was exit by "exit"
// Maybe I'm gonna add other cases where it is acceptable for the shell to quit
// and so revive it too.
static void	re_launch_process(void)
{
	char	*pid;
	char	*cmd;

	if (!(cmd = (char *)malloc(sizeof(char) * (strlen(g_cmdline) + 2))))
	{
		perror("malloc");
		exit (1);
	}
	strcat(cmd, g_cmdline);
	strcat(cmd, "\n");
	send_input(cmd);
	free(cmd);
	exit(1);
	pid = get_new_process_pid();
	load_target_info(pid);
	free(pid);
}

static void	wait_end_cmd(void)
{
	char	*wchan;
	int		nb_tried;
	int		stop = 3;


}

// This function send a cmd to a process with ioctl, storing the
// input into the queue of desired process.
static void	send_input(char *input)
{
	int				i;

	i = 0;
	while (input[i])
	{
		if (ioctl(g_fd, TIOCSTI, &(input[i])) < 0)
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
	if (!strchr(input, '\n'))
		return ;

	usleep(DELAY_TIME * INPUT_DELAY);
	wait_end_cmd();

	input[strlen(input) - 1] = '\0';
	if (PROCESS_STOPPED && !ft_strequ(input, g_cmdline))
	{
		if (strstr(input, "exit"))
			re_launch_process();
		else
		{
			dprintf(2, "process quit\n");
			exit(1);
		}
	}
}

static void	open_and_exec_file(char *file)
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
		send_input(line);
	printf("\033[37m[done]\033[0m\n");
	fclose(fp);
}

static void	exec_all_tests(int pid)
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
			open_and_exec_file(file->d_name);
		}
	}
	closedir(dirp);
}

static int	is_str_digit(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	// Some basic verifications
	if (argc < 2)
	{
		dprintf(2, "Interactive_test: no pid given, make sure an instance of wanted"\
				" program is already running, and then use 'make interactive_test" \
				" [FILES=\"file1 file2 ...\"]'.\n");
		return (1);
	}

	if (ft_strequ(argv[2], "-h"))
	{
		printf("interactive_test send each line of your test files to your interactive"\
				" program.\nTo use it, just run an instance of your program in another terminal, and run 'make interactive_test [FILES=\"file1 file2 ...\"]'.\n"\
				"Each 'file' should be placed in the same directory as interactive_test.c."\
				" If several instance of your program are runnning, Interactive_test is gonna test one of the running instance, but you cannot know wich one." \
				" Having only running instance is advised.\n");
	}

	load_target_info(argv[1]);

	int				i = 2;
	int				status;

	g_pid = atoi(argv[1]);
	while (argv[i] && is_str_digit(argv[i]))
		i++;
	// If the user specify file test, launch them.
	if (argv[i])
	{
		while (argv[i])
		{
			open_and_exec_file(argv[i]);
			i++;
		}
	}
	// else exec all *.test in current directory
	else
		exec_all_tests(g_pid);
	free(g_process_input);
	close(g_fd);
}
