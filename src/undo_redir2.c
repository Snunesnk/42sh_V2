/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:33:28 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/21 12:38:20 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int		undo_iowrite(t_redirection *r)
{
	if (r->save[0] != -1)
	{
		dup2(r->save[0], r->redirector.dest);
		close(r->save[0]);
	}
	return (0);
}

int		undo_ioread(t_redirection *r)
{
	if (r->redirectee.dest == r->redirector.dest && !(r->flags & FDCLOSE))
		return (0);
	if (r->save[0] != -1)
	{
		dup2(r->save[0], r->redirectee.dest);
		close(r->save[0]);
	}
	return (0);
}

int		undo_iodup(t_redirection *r)
{
	if (r->redirectee.dest == r->redirector.dest && !(r->flags & FDCLOSE))
		return (0);
	if (r->save[0] != -1)
	{
		dup2(r->save[0], r->redirector.dest);
		close(r->save[0]);
	}
	return (0);
}

int		undo_iodfile(t_redirection *r)
{
	if (r->redirectee.dest == r->redirector.dest)
		return (0);
	close(r->redirectee.dest);
	if (r->save[0] != -1)
	{
		dup2(r->save[0], STDOUT_FILENO);
		close(r->save[0]);
	}
	if (r->save[1] != -1)
	{
		dup2(r->save[1], STDERR_FILENO);
		close(r->save[1]);
	}
	return (0);
}

int		undo_redirection(t_redirection *r)
{
	if (r && (r->flags & REDSUC))
	{
		undo_redirection(r->next);
		if (r->instruction == IOWRITE)
			undo_iowrite(r);
		else if (r->instruction == IOCAT)
			undo_iowrite(r);
		else if (r->instruction == IOREAD)
			undo_ioread(r);
		else if (r->instruction == (IODUP | IOWRITE))
			undo_iodfile(r);
		else if (r->instruction == (IODUP | IOREAD))
			undo_ioread(r);
		else if (r->instruction == IODUP)
			undo_iodup(r);
	}
	return (0);
}
