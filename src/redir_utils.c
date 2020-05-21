/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:20:26 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/21 12:48:57 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define FD_BASE 10

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

static int	unsued_fd(t_redirection *r)
{
	t_redirection	*origin;
	int				fd;

	fd = FD_BASE;
	origin = r;
	while (r)
	{
		if (r->redirectee.dest == fd
			|| r->redirector.dest == fd
			|| fcntl(fd, F_GETFD) >= 0)
		{
			++fd;
			r = origin;
			continue;
		}
		r = r->next;
	}
	return (fd);
}

int			dupit(int fd, t_redirection *r)
{
	int	save_fd;
	int	available_fd;

	if (fcntl(fd, F_GETFD) < 0)
		return (-1);
	available_fd = unsued_fd(r);
	save_fd = fcntl(fd, F_DUPFD, available_fd);
	if (save_fd < 0)
		return (-1);
	fcntl(save_fd, F_SETFD, FD_CLOEXEC);
	return (save_fd);
}
