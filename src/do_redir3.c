/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:30:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 16:34:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	do_redir_disp(t_redirection *r)
{
	int	error;

	error = 0;
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
	return (error);
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
		error = do_redir_disp(r);
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
