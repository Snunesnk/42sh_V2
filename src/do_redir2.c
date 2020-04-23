/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/23 14:09:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int	do_iohere(t_redirection *r)
{
	if (valid_fd(r->redirectee.dest, 1))
		return (e_bad_file_descriptor);
	if (write(r->redirectee.dest, r->redirector.hereword,
				ft_strlen(r->redirector.hereword)) < 0)
		return (psherror(e_system_call_error, "write(2)", e_cmd_type));
	return (0);
}

int	do_iodfile(t_redirection *r)
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
				O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
		return (psherror(e_system_call_error, "open(2)", e_cmd_type));
	if (r->flags & NOFORK)
		r->save[0] = dup(STDOUT_FILENO);
	if (r->flags & NOFORK)
		r->save[1] = dup(STDERR_FILENO);
	dup2(r->redirectee.dest, STDOUT_FILENO);
	dup2(r->redirectee.dest, STDERR_FILENO);
	close(r->redirectee.dest);
	return (0);
}

int	do_iodread(t_redirection *r)
{
	if (r->flags & FDCLOSE)
	{
		if (r->flags & NOFORK)
			r->save[0] = dup(r->redirectee.dest);
		close(r->redirectee.dest);
	}
	else if (r->flags & FILENAME)
		return (psherror(e_ambiguous_redirect,
					r->redirector.filename, e_cmd_type));
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

int	do_iodup(t_redirection *r)
{
	if (r->flags & FILENAME && r->redirector.dest != STDOUT_FILENO)
		return (psherror(e_ambiguous_redirect,
					r->redirectee.filename, e_cmd_type));
	else if (r->flags & FILENAME)
	{
		r->instruction |= IOWRITE;
		return (do_iodfile(r));
	}
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
