/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:20:26 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/21 12:22:35 by abarthel         ###   ########.fr       */
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
	int			fd;

	fd = 0; // Should be replaced by FD_BASE if algro works
	origin = r;
	while (r)
	{
		if (r->redirectee.dest == fd
			|| r->redirector.dest == fd
			|| fcntl(fd, F_GETFD) >= 0)
		{
			++fd;
			ft_dprintf(255, "|%d|\n", fd);
			r = origin;
			continue;
		}
		r = r->next;
	}
	return (fd);
}

int	dupfd(int fd, t_redirection *r)
{
	int	save_fd;
	int	flag;

	if (fcntl(fd, F_GETFD) < 0)
		return (-1);
	flag = unsued_fd(r);
	ft_dprintf(255, "%d\n", flag);
	save_fd = fcntl(fd, F_GETFD);
	return (save_fd);

}
