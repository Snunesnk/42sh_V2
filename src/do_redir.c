/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/20 15:34:07 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int	valid_fd(char *s, int fd, int open)
{
	if (open)
	{
		if (fd >= sysconf(_SC_OPEN_MAX) || fcntl(fd, F_GETFL) < 0)
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: Bad file descriptor\n", g_progname, s);
			return (1);
		}
	}
	else if (fd >= sysconf(_SC_OPEN_MAX))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: Bad file descriptor\n", g_progname, s);
		return (1);
	}
	return (0);
}

int	check_if_directory(char *filename)
{
	struct stat	buf;

	buf = (struct stat){.st_mode = 0};
	if (stat(filename, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
		return (psherror(e_is_a_directory, filename, e_cmd_type));
	return (0);
}

int	do_iowrite(t_redirection *r)
{
	if (check_if_directory(r->redirectee.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
				O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
		return (psherror(e_permission_denied,
					r->redirectee.filename, e_cmd_type));
	else
		r->redirectee.dest = open(r->redirectee.filename,
				O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
		return (psherror(e_system_call_error, "open(2)", e_cmd_type));
	if (valid_fd(r->redirector.filename, r->redirector.dest, 0))
	{
		close(r->redirectee.dest);
		return (e_bad_file_descriptor);
	}
	if (r->flags & NOFORK)
		r->save[0] = dup(r->redirector.dest);
	dup2(r->redirectee.dest, r->redirector.dest);
	close(r->redirectee.dest);
	return (0);
}

int	do_iocat(t_redirection *r)
{
	if (check_if_directory(r->redirectee.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
		O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
		return (psherror(e_permission_denied,
						r->redirectee.filename, e_cmd_type));
	else
		r->redirectee.dest = open(r->redirectee.filename,
				O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
		return (psherror(e_system_call_error, "open(2)", e_cmd_type));
	if (valid_fd(r->redirector.filename, r->redirector.dest, 0))
	{
		close(r->redirectee.dest);
		return (e_bad_file_descriptor);
	}
	if (r->flags & NOFORK)
		r->save[0] = dup(r->redirector.dest);
	dup2(r->redirectee.dest, r->redirector.dest);
	close(r->redirectee.dest);
	return (0);
}

int	do_ioread(t_redirection *r)
{
	if (check_if_directory(r->redirector.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (valid_fd(r->redirectee.filename, r->redirectee.dest, 0))
		return (e_bad_file_descriptor);
	else if (access(r->redirector.filename, F_OK))
		return (psherror(e_redir_no_file,
				r->redirector.filename, e_cmd_type));
	else if (access(r->redirector.filename, R_OK))
	{
		return (psherror(e_permission_denied,
					r->redirector.filename, e_cmd_type));
	}
	r->redirector.dest = open(r->redirector.filename, O_RDONLY);
	if (r->redirector.dest < 0)
		return (psherror(e_system_call_error, "open(2)", e_cmd_type));
	if (r->flags & NOFORK)
		r->save[0] = dup(r->redirectee.dest);
	dup2(r->redirector.dest, r->redirectee.dest);
	close(r->redirector.dest);
	return (0);
}
