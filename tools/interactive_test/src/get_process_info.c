#include "interactive_test.h"

int			get_process_group(char *pid)
{
	char	*autogroup;
	char	line[1024];
	int		start = 0; 
	int		end = 0;
	int		fd;

	if (!(autogroup = (char *)malloc(sizeof(char) * (strlen("/proc//autogroup") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	bzero(autogroup, (strlen("/proc//autogroup") + strlen(pid) + 1));
	sprintf(autogroup, "/proc/%s/autogroup", pid);
	if (access(autogroup, F_OK))
	{
		free(autogroup);
		return (0);
	}
	if ((fd = open(autogroup, O_RDONLY)) < 0)
	{
		perror("open failed in get_process_group");
		exit(1);
	}
	bzero(line, 1024);
	read(fd, line, 1023);
	close(fd);
	while (line[start] && !isdigit(line[start]))
		start++;
	end = start;
	while (line[end] && isdigit(line[end]))
		end++;
	line[end] = '\0';
	free(autogroup);
	return (atoi(line + start));
}

// Open desired process input
t_process	load_target_info(t_process process, char *pid)
{
	char		*cmdline_file;
	int			cmdline_fd;
	char		tmp_buf[1024];

	if (!(process.process_input = (char *)malloc(sizeof(char) * (strlen("/proc//fd/0") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	bzero(process.process_input, (strlen("/proc//fd/0") + strlen(pid) + 1));
	if (!(process.wchan = (char *)malloc(sizeof(char) * (strlen("/proc//wchan") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	bzero(process.wchan, (strlen("/proc//wchan") + strlen(pid) + 1));
	if (!(cmdline_file = (char *)malloc(sizeof(char) * (strlen("/proc//cmdline") \
						+ strlen(pid) + 1))))
	{
		perror("malloc");
		exit(1);
	}
	bzero(cmdline_file, (strlen("/proc//cmdline") + strlen(pid) + 1));
	sprintf(process.process_input, "/proc/%s/fd/0", pid);
	sprintf(cmdline_file, "/proc/%s/cmdline", pid);
	sprintf(process.wchan, "/proc/%s/wchan", pid);
	//open input fd of desired process
	if ((process.fd = open(process.process_input, O_RDWR)) < 0)
	{
		perror("open");
		exit(1);
	}
	// open cmdline file of process, to know how was it launch, to be able to launch
	// it in the exact same way
	if ((cmdline_fd = open(cmdline_file, O_RDONLY)) < 0)
	{
		perror("open");
		exit(1);
	}
	free(cmdline_file);
	bzero(tmp_buf, 1024);

	char	*tmp;

	while (read(cmdline_fd, tmp_buf, 1023))
	{
		tmp = process.cmdline;
		process.cmdline = ft_strjoin(process.cmdline, tmp_buf);
		free(tmp);
		bzero(tmp_buf, strlen(tmp_buf));
	}
	close(cmdline_fd);
	process.pid = atoi(pid);
	process.group = get_process_group(pid);
	return (process);
}
