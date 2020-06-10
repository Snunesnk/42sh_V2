#include "interactive_test.h"

t_process g_target_process = {
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
	while (fgets(line, 1024, fp) != NULL)
	{
		i = 0;
		dont = 0;
		tmp = input;
		input = ft_strjoin(input, line);
		free(tmp);
		while (!strchr(input, '\n'))
		{
			bzero(line, 1024);
			fgets(line, 1023, fp);
			tmp = input;
			input = ft_strjoin(input, line);
			free(tmp);
		}
		while (unsupported[i])
		{
			if (strstr(unsupported[i], line))
			{
				dont = 1;
				break ;
			}
			i++;
		}
		if (dont)
		{
			bzero(line, 1024);
			continue ;
		}
		send_input(line, process);
		usleep(INPUT_DELAY);
		process = get_active_process(process, line);
		bzero(line, 1024);
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

	g_target_process = load_target_info(g_target_process, argv[1]);

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
	free(g_target_process.process_input);
	free(g_target_process.cmdline);
	free(g_target_process.wchan);
	close(g_target_process.fd);
}
