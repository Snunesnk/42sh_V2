/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/06 20:56:21 by snunes           ###   ########.fr       */
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

/* Seems ok */
static int	do_iowrite(t_redirection *r)
{
	struct stat     buf;

	buf = (struct stat){.st_mode = 0};
	if (stat(r->redirectee.filename, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
	{
		psherror(e_is_a_directory, r->redirectee.filename, e_cmd_type);
		return (e_is_a_directory);
	}
	if (access(r->redirectee.filename, F_OK))
	{ /* File does not exists so attempt to create it */
		r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (access(r->redirectee.filename, R_OK))
	{ /* File exists but no rights to write */
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else /* File exists and rights to write */
		r->redirectee.dest = open(r->redirectee.filename, O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{ /* Open error */
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

/* Seems ok */
static int	do_iocat(t_redirection *r)
{
	struct stat     buf;

	buf = (struct stat){.st_mode = 0};
	if (stat(r->redirectee.filename, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
	{
		psherror(e_is_a_directory, r->redirectee.filename, e_cmd_type);
		return (e_is_a_directory);
	}
	if (access(r->redirectee.filename, F_OK))
	{ /* File does not exists so attempt to create it */
		r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (access(r->redirectee.filename, R_OK))
	{ /* File exists but no rights to write */
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else /* File exists and rights to write */
		r->redirectee.dest = open(r->redirectee.filename, O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{ /* Open error */
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

/* Seems ok */
static int	do_ioread(t_redirection *r)
{
	struct stat     buf;

	buf = (struct stat){.st_mode = 0};
	if (valid_fd(r->redirectee.dest, 0))
		return (e_bad_file_descriptor);
	if (stat(r->redirector.filename, &buf)) /* Optional for read, not default behavior */
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
	{
		psherror(e_is_a_directory, r->redirector.filename, e_cmd_type);
		return (e_is_a_directory);
	}
	if (access(r->redirector.filename, F_OK))
	{
		psherror(e_no_such_file_or_directory, r->redirector.filename, e_cmd_type);
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

/* Seems ok */
static int	do_iohere(t_redirection *r)
{
	if (valid_fd(r->redirectee.dest, 1))
		return (e_bad_file_descriptor);
	/* Could segv if hereword is empty string, should free heredoc string */
	if (write(r->redirectee.dest, r->redirector.hereword, ft_strlen(r->redirector.hereword)) < 0)
	{
		psherror(e_system_call_error, "write(2)", e_cmd_type);
		/* Free heredoc string ? */
		return (e_system_call_error);
	}
	return (0);
}

static int	do_iodfile(t_redirection *r)
{
	struct stat     buf;

	buf = (struct stat){.st_mode = 0};
	if (stat(r->redirectee.filename, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
	{
		psherror(e_is_a_directory, r->redirectee.filename, e_cmd_type);
		return (e_is_a_directory);
	}
	/* Open file */
	if (access(r->redirectee.filename, F_OK))
	{ /* File does not exists so attempt to create it */
		r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (access(r->redirectee.filename, R_OK))
	{ /* File exists but no rights to write */
		psherror(e_permission_denied, r->redirectee.filename, e_cmd_type);
		return (e_permission_denied);
	}
	else /* File exists and rights to write */
		r->redirectee.dest = open(r->redirectee.filename, O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{ /* Open error */
		psherror(e_system_call_error, "open(2)", e_cmd_type);
		return (e_system_call_error);
	}
	/* Dup err and out */
	if (r->flags & NOFORK)
		r->save[0] = dup(STDOUT_FILENO);
	if (r->flags & NOFORK)
		r->save[1] = dup(STDERR_FILENO);
	dup2(r->redirectee.dest, STDOUT_FILENO);
	dup2(r->redirectee.dest, STDERR_FILENO);
	close(r->redirectee.dest);
	return (0);
}

/* CANNOT PROPERLY TEST */
static int	do_iodread(t_redirection *r)
{
	if (r->flags & FDCLOSE)
	{ /* [n]<&- */
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		close(r->redirectee.dest);
	}
	else if (r->flags & FILENAME)
	{ /* [n]<&filename */
		psherror(e_ambiguous_redirect, r->redirector.filename, e_cmd_type);
		return (e_ambiguous_redirect);
	}
	else if (r->flags & DEST)
	{ /* [n]<&n */
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
	{ /* n>&filename: ok */
		psherror(e_ambiguous_redirect, r->redirectee.filename, e_cmd_type);
		return (e_ambiguous_redirect);
	}
	else if (r->flags & FILENAME)
	{ /* >&filename: equivalent to >filename 2>&1 or to &>filename*/
		return (do_iodfile(r));
	}
	else if (r->flags & DEST)
	{ /* [n]>&n: ok*/
		if (valid_fd(r->redirectee.dest, 1))
			return (e_bad_file_descriptor);
		if (r->redirectee.dest == r->redirector.dest)
			return (0);
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		dup2(r->redirectee.dest, r->redirector.dest);
	}
	else if (r->flags & FDCLOSE)
	{ /* [n]>&-: ok */
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirector.dest);
		close(r->redirector.dest);
	}
	return (0);
}

int	do_redirection(t_redirection *r)
{
	/* Used for error type and displaying the correct error message in process.c */
	int		error;
	t_redirection	*beg;

	beg = r;
	error = 0;
	while (r)
	{
		if (r->error)
		{
			if (r->flags & NOFORK) /* NO FORK should be set to all redir */
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
			if (r->flags & NOFORK) /* NO FORK should be set to all redir */
				undo_redirection(beg);
			return (error);
		}
		r->flags |= REDSUC;
		r = r->next;
	}
	return (0);
}
