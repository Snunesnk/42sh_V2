/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/06/12 16:25:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

#define ESYSOP "open(2) cannot create temp file for here-document"

#ifndef __unix__
# define FL1 O_CREAT
# define FL2 O_TRUNC
# define TMPFILE "/tmp/monkeyshell.tmp"

#else
# define FL1 __O_TMPFILE
# define FL2 0x0
# define TMPFILE "/tmp"

#endif

int	do_iohere(t_redirection *r, t_redirection *beg)
{
	if (valid_fd(r->redirectee.filename, r->redirectee.dest, 0))
		return (e_bad_file_descriptor);
	r->redirector.dest = open(TMPFILE, FL1 | FL2 | O_RDWR, S_IRUSR | S_IWUSR);
	if (r->redirector.dest < 0)
		return (psherror(e_system_call_error, ESYSOP, e_cmd_type));
	if (write(r->redirector.dest, r->redirector.hereword,
		ft_strlen(r->redirector.hereword)) < 0)
		return (psherror(e_system_call_error, "write(2)", e_cmd_type));
	lseek(r->redirector.dest, 0, SEEK_SET);
	r->instruction = IOREAD;
	if (r->flags & NOFORK)
		r->save[0] = dupit(r->redirectee.dest, beg);
	if (r->redirector.dest != r->redirectee.dest)
		dup2(r->redirector.dest, r->redirectee.dest);
	return (0);
}

int	do_iodfile(t_redirection *r, t_redirection *b)
{
	int	err;

	if ((err = check_if_directory(r->redirectee.filename)))
		return (err);
	else if (access(r->redirectee.filename, F_OK))
		r->redirectee.dest = open(r->redirectee.filename,
	O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (access(r->redirectee.filename, R_OK))
		return (psherror(e_redir_denied, r->redirectee.filename, e_cmd_type));
	else
		r->redirectee.dest = open(r->redirectee.filename,
	O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
		return (psherror(e_redir_no_file, r->redirectee.filename, e_cmd_type));
	r->save[0] = r->flags & NOFORK ? dupit(STDOUT_FILENO, b) : r->save[0];
	if (r->flags & NOFORK)
		r->save[1] = dupit(STDERR_FILENO, b);
	if (r->redirectee.dest != STDOUT_FILENO
		&& r->redirectee.dest != STDERR_FILENO)
	{
		dup2(r->redirectee.dest, STDOUT_FILENO);
		dup2(r->redirectee.dest, STDERR_FILENO);
		close(r->redirectee.dest);
	}
	return (0);
}

int	do_iodread(t_redirection *r, t_redirection *beg)
{
	if (r->flags & FDCLOSE)
	{
		if (fd_need_be_open(r))
			return (0);
		if (r->flags & NOFORK)
			r->save[0] = dupit(r->redirectee.dest, beg);
		close(r->redirectee.dest);
	}
	else if (r->flags & FILENAME)
		return (psherror(e_ambiguous_redirect,
					r->redirector.filename, e_cmd_type));
	else if (r->flags & DEST)
	{
		if (r->redirectee.dest == r->redirector.dest)
			return (0);
		if (valid_fd(r->redirector.filename, r->redirector.dest, 1))
			return (e_bad_file_descriptor);
		if (r->flags & NOFORK)
			r->save[0] = dupit(r->redirectee.dest, beg);
		dup2(r->redirector.dest, r->redirectee.dest);
	}
	return (0);
}

int	do_iodup(t_redirection *r, t_redirection *beg)
{
	if (r->flags & FILENAME && r->redirector.dest != STDOUT_FILENO)
		return (psherror(e_ambiguous_redirect,
					r->redirectee.filename, e_cmd_type));
	else if (r->flags & FILENAME)
	{
		r->instruction |= IOWRITE;
		return (do_iodfile(r, beg));
	}
	else if (r->flags & DEST)
	{
		if (r->redirectee.dest == r->redirector.dest)
			return (0);
		if (valid_fd(r->redirectee.filename, r->redirectee.dest, 1))
			return (e_bad_file_descriptor);
		r->save[0] = r->flags & NOFORK ? dup(r->redirector.dest) : r->save[0];
		dup2(r->redirectee.dest, r->redirector.dest);
	}
	else if (r->flags & FDCLOSE && !fd_need_be_open(r))
	{
		if (r->flags & NOFORK)
			r->save[0] = dupit(r->redirector.dest, beg);
		if (r->redirectee.dest != r->redirector.dest)
			close(r->redirector.dest);
	}
	return (0);
}
