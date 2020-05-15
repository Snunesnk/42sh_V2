/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:20:26 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 16:41:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	read_open(t_redirection *r)
{
	t_redirection	*origin;
	int				fd;

	origin = r;
	fd = r->redirectee.dest;
	r = r->next;
	while (r)
	{
		if ((r->instruction & IOREAD || r->instruction & IOHERE)
			&& r->redirectee.dest == fd)
		{
			origin->instruction = IONONE;
			return (1);
		}
		r = r->next;
	}
	return (0);
}

static int	dup_open(t_redirection *r)
{
	t_redirection	*origin;
	int				fd;

	origin = r;
	fd = r->redirector.dest;
	r = r->next;
	while (r)
	{
		if ((r->instruction & IOWRITE || r->instruction & IOCAT
			|| r->instruction & IODUP)
			&& r->redirector.dest == fd)
		{
			origin->instruction = IONONE;
			return (1);
		}
		r = r->next;
	}
	return (0);
}

int			fd_need_be_open(t_redirection *r)
{
	if (r->instruction & IOREAD)
		return (read_open(r));
	else
		return (dup_open(r));
	return (0);
}
