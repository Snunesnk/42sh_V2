/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:33:28 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 15:16:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int		undo_iowrite(t_redirection *r, t_shell_fds **shell_fd)
{
	if (!restored_fd(*shell_fd, r->redirector.dest))
	{
		add_restored_fd(shell_fd, r->redirector.dest);
		dup2(r->save[0], r->redirector.dest);
	}
	close(r->save[0]);
	return (0);
}

int		undo_ioread(t_redirection *r, t_shell_fds **shell_fd)
{
	if (r->redirectee.dest == r->redirector.dest)
		return (0);
	if (!restored_fd(*shell_fd, r->redirectee.dest))
	{
		add_restored_fd(shell_fd, r->redirectee.dest);
		dup2(r->save[0], r->redirectee.dest);
	}
	close(r->save[0]);
	return (0);
}

int		undo_iodup(t_redirection *r, t_shell_fds **shell_fd)
{
	if (r->redirectee.dest == r->redirector.dest)
		return (0);
	if (!restored_fd(*shell_fd, r->redirectee.dest))
	{
		add_restored_fd(shell_fd, r->redirectee.dest);
		dup2(r->save[0], r->redirector.dest);
	}
	close(r->save[0]);
	return (0);
}

int		undo_iodfile(t_redirection *r, t_shell_fds **shell_fd)
{
	if (r->redirectee.dest == r->redirector.dest)
		return (0);
	close(r->redirectee.dest);
	if (!restored_fd(*shell_fd, STDOUT_FILENO))
	{
		add_restored_fd(shell_fd, STDOUT_FILENO);
		dup2(r->save[0], STDOUT_FILENO);
	}
	close(r->save[0]);
	if (!restored_fd(*shell_fd, STDERR_FILENO))
	{
		add_restored_fd(shell_fd, STDERR_FILENO);
		dup2(r->save[1], STDERR_FILENO);
	}
	close(r->save[1]);
	return (0);
}

int		undo_redirection_internal(t_redirection *r)
{
	t_shell_fds	*shell_fd;

	shell_fd = NULL;
	while (r)
	{
		if (r->flags & REDSUC)
		{
			if (r->instruction == IOWRITE)
				undo_iowrite(r, &shell_fd);
			else if (r->instruction == IOCAT)
				undo_iowrite(r, &shell_fd);
			else if (r->instruction == IOREAD)
				undo_ioread(r, &shell_fd);
			else if (r->instruction == (IODUP | IOWRITE))
				undo_iodfile(r, &shell_fd);
			else if (r->instruction == IODUP && !(r->flags & FDCLOSE))
				undo_iodup(r, &shell_fd);
			else if (r->instruction == (IODUP | IOREAD)
					&& !(r->flags & FDCLOSE))
				undo_ioread(r, &shell_fd);
		}
		r = r->next;
	}
	free_restored_fd(shell_fd);
	return (0);
}
