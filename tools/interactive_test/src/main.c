#include "interactive_test.h"

t_process g_target_process = {
	.pid = 0,
	.fd = -1,
	.group = 0,
	.process_input = NULL,
	.cmdline = NULL,
	.wchan = NULL
};

t_process g_base_process = {
	.pid = 0,
	.fd = -1,
	.group = 0,
	.process_input = NULL,
	.cmdline = NULL,
	.wchan = NULL
};

static void	open_and_exec_file(char *file)
{
	FILE		*fp;
	t_process	process;
	char		*(unsupported[4]);

	unsupported[0] = "vim";
	unsupported[1] = "emacs";
	unsupported[2] = "nano";
	unsupported[3] = NULL;
	printf("\033[36mLaunch %s\033[0m\n", get_filename(file));
	if (!(fp = fopen(file, "r")))
	{
		perror("fopen");
		return ;
	}
	free(file);

	char	line[1024];
	char	*tmp;
	char	*input;
	int		i;
	int		dont;

	input = NULL;
	bzero(line, 1024);
	process = g_target_process;
	while (fgets(line, 1023, fp) != NULL)
	{
		i = 0;
		dont = 0;
		tmp = input;
		input = ft_strjoin(input, line);
		free(tmp);
		while (!strchr(input, '\n'))
		{
			bzero(line, 1024);
			if (fgets(line, 1023, fp) == NULL)
				break ;
			tmp = input;
			input = ft_strjoin(input, line);
			free(tmp);
		}
		while (unsupported[i])
		{
			if (strstr(input, unsupported[i]))
			{
				dont = 1;
				break ;
			}
			i++;
		}
		if (dont)
		{
			bzero(line, 1024);
			free(input);
			input = NULL;
			continue ;
		}
		is_ready(process.wchan); // when process is still receiving input / processing,
		send_input(input, process);
		is_ready(process.wchan); // when process is still receiving input / processing,
		// wchan contains 0. is_ready() is gonna loop while wchan contains 0, then return
		// when wchan contains wait_woken or do_wait, or something else indicating that
		// process has red input and is executing a cmd / waiting for input
		process = get_active_process(process, input);
		bzero(line, 1024);
		free(input);
		input = NULL;
	}
	printf("\033[37m[done]\033[0m\n");
	fclose(fp);
}

static void	exec_all_tests(void)
{
	DIR				*dirp;
	struct dirent	*file;
	int				ext_name = strlen(TEST_EXT);
	int				name_len;

	dirp = opendir(TEST_DIR);
	while ((file = readdir(dirp)))
	{
		name_len = strlen(file->d_name);
		if (name_len > ext_name && ft_strequ(file->d_name + name_len - ext_name, TEST_EXT) \
					&& file->d_name[0] != '.')
		{
			open_and_exec_file(ft_strjoin(TEST_DIR, file->d_name));
		}
	}
	closedir(dirp);
}

char	*get_base_proc_pid(void)
{
	DIR				*dirp;
	struct dirent	*file;
	char			line[1024];

	bzero(line, 1024);
	if (!(dirp = opendir("/proc")))
	{
		perror("opendir failed in get_base_proc_pid");
		exit(1);
	}
	while ((file = readdir(dirp)))
	{
		if (file->d_name[0] == '.' || !is_str_digit(file->d_name))
			continue ;
		bzero(line, 1024);
		if (g_target_process.group != get_process_group(file->d_name))
			continue ;
		break ;
	}
	strcpy(line, file->d_name);
	closedir(dirp);
	return (strdup(line));
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
		printf("\ninteractive_test send each line of your test files to your interactive"\
				" program.\nTo use it, just run an instance of your program in another terminal, and run 'make interactive_test [FILES=\"file1 file2 ...\"]'.\n"\
				"Each 'file' should be placed in the same directory as interactive_test.c.\n"\
				"If several instance of your program are runnning, Interactive_test is gonna test one of the running instance, but you cannot know wich one." \
				" Having only one running instance is advised.\n");
		printf("You can change time between each char sent, time before stopping a process and time between each line sent in include/define.h\n");
		return (0);
	}

	g_target_process = load_target_info(g_target_process, argv[1]);

	char	*b_pid;
	b_pid = get_base_proc_pid();
	g_base_process = load_target_info(g_base_process, b_pid);
	free(b_pid);

	int				i = 2;

	while (argv[i] && is_str_digit(argv[i]))
		i++;
	// If the user specify file test, launch them.
	if (argv[i])
	{
		while (argv[i])
		{
			open_and_exec_file(ft_strjoin(TEST_DIR, argv[i]));
			i++;
		}
	}
	// else exec all *.test in current directory
	else
		exec_all_tests();
	free_process(&g_target_process);
	free_process(&g_base_process);
}
