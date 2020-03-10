/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 16:06:07 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	valid_fd(int fd, int open)
{
	if (open)
	{
		if (fd >= sysconf(_SC_OPEN_MAX) || fcntl(fd, F_GETFL) < 0)
		{
			ft_printf("%s: %d: Bad file descriptor\n", g_progname, fd);
			return (1);
		}
	}
	else if (fd >= sysconf(_SC_OPEN_MAX))
	{
		ft_printf("%s: %d: Bad file descriptor\n", g_progname, fd);
		return (1);
	}
	return (0);
}

static int	check_if_directory(char *filename)
{
	struct stat	buf;

	buf = (struct stat){.st_mode = 0};
	if (stat(filename, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
	{
		psherror(e_is_a_directory, filename, e_cmd_type);
		return (e_is_a_directory);
	}
	return (0);
}

static int	do_iowrite(t_redirection *r)
{
	if (check_if_directory(r->redirectee.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
				O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
	{
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else
		r->redirectee.dest = open(r->redirectee.filename,
				O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{
		psherror(e_system_call_error, "open(2)", e_cmd_type);
		return (e_system_call_error);
	}
	if (valid_fd(r->redirector.dest, 0))
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

static int	do_iocat(t_redirection *r)
{
	if (check_if_directory(r->redirectee.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
		O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
	{
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else
		r->redirectee.dest = open(r->redirectee.filename,
				O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{
		psherror(e_system_call_error, "open(2)", e_cmd_type);
		return (e_system_call_error);
	}
	if (valid_fd(r->redirector.dest, 0))
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

static int	do_ioread(t_redirection *r)
{
	if (check_if_directory(r->redirector.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (valid_fd(r->redirectee.dest, 0))
		return (e_bad_file_descriptor);
	else if (access(r->redirector.filename, F_OK))
	{
		psherror(e_no_such_file_or_directory,
				r->redirector.filename, e_cmd_type);
		return (e_no_such_file_or_directory);
	}
	else if (access(r->redirector.filename, R_OK))
	{
		psherror(e_permission_denied, r->redirector.filename, e_cmd_type);
		return (e_permission_denied);
	}
	r->redirector.dest = open(r->redirector.filename, O_RDONLY);
	if (r->redirector.dest < 0)
	{
		psherror(e_system_call_error, "open(2)", e_cmd_type);
		return (e_system_call_error);
	}
	if (r->flags & NOFORK)
		r->save[0] = dup(r->redirectee.dest);
	dup2(r->redirector.dest, r->redirectee.dest);
	close(r->redirector.dest);
	return (0);
}

static int	do_iohere(t_redirection *r)
{
	if (valid_fd(r->redirectee.dest, 1))
		return (e_bad_file_descriptor);
	if (write(r->redirectee.dest, r->redirector.hereword,
				ft_strlen(r->redirector.hereword)) < 0)
	{
		psherror(e_system_call_error, "write(2)", e_cmd_type);
		return (e_system_call_error);
	}
	return (0);
}

static int	do_iodfile(t_redirection *r)
{
	if (check_if_directory(r->redirectee.filename) == e_is_a_directory)
		return (e_is_a_directory);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
				O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
	{
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else
		r->redirectee.dest = open(r->redirectee.filename,
				O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{
		psherror(e_system_call_error, "open(2)", e_cmd_type);
		return (e_system_call_error);
	}
	if (r->flags & NOFORK)
		r->save[0] = dup(STDOUT_FILENO);
	if (r->flags & NOFORK)
		r->save[1] = dup(STDERR_FILENO);
	dup2(r->redirectee.dest, STDOUT_FILENO);
	dup2(r->redirectee.dest, STDERR_FILENO);
	close(r->redirectee.dest);
	return (0);
}

static int	do_iodread(t_redirection *r)
{
	if (r->flags & FDCLOSE)
	{
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		close(r->redirectee.dest);
	}
	else if (r->flags & FILENAME)
	{
		psherror(e_ambiguous_redirect, r->redirector.filename, e_cmd_type);
		return (e_ambiguous_redirect);
	}
	else if (r->flags & DEST)
	{
		if (valid_fd(r->redirector.dest, 1))
			return (e_bad_file_descriptor);
		if (r->redirectee.dest == r->redirector.dest)
			return (0);
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirectee.dest);
		dup2(r->redirector.dest, r->redirectee.dest);
	}
	return (0);
}

static int	do_iodup(t_redirection *r)
{
	if (r->flags & FILENAME && r->redirector.dest != STDOUT_FILENO)
	{
		psherror(e_ambiguous_redirect, r->redirectee.filename, e_cmd_type);
		return (e_ambiguous_redirect);
	}
	else if (r->flags & FILENAME)
		return (do_iodfile(r));
	else if (r->flags & DEST)
	{
		if (valid_fd(r->redirectee.dest, 1))
			return (e_bad_file_descriptor);
		if (r->redirectee.dest == r->redirector.dest)
			return (0);
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		dup2(r->redirectee.dest, r->redirector.dest);
	}
	else if (r->flags & FDCLOSE)
	{
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		close(r->redirector.dest);
	}
	return (0);
}

int			do_redirection(t_redirection *r)
{
	int				error;
	t_redirection	*beg;

	beg = r;
	error = 0;
	while (r)
	{
		if (r->error)
		{
			if (r->flags & NOFORK)
				undo_redirection(beg);
			return (g_errordesc[r->error].code);
		}
		if (r->instruction == IOWRITE)
			error = do_iowrite(r);
		else if (r->instruction == IOCAT)
			error = do_iocat(r);
		else if (r->instruction == IOREAD)
			error = do_ioread(r);
		else if (r->instruction == IOHERE)
			error = do_iohere(r);
		else if (r->instruction == IODUP)
			error = do_iodup(r);
		else if (r->instruction == (IODUP | IOREAD))
			error = do_iodread(r);
		else if (r->instruction == (IODUP | IOWRITE))
			error = do_iodfile(r);
		if (error)
		{
			if (r->flags & NOFORK)
				undo_redirection(beg);
			return (error);
		}
		r->flags |= REDSUC;
		r = r->next;
	}
	return (0);
}
