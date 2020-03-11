/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:33:28 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 16:20:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int		restored_fd(t_shell_fds *shell_fd, int fd)
{
	while (shell_fd)
	{
		if (shell_fd->fd == fd)
			return (1);
		shell_fd = shell_fd->next;
	}
	return (0);
}

void	add_restored_fd(t_shell_fds **shell_fd, int add)
{
	t_shell_fds	*s;

	if (!*shell_fd)
	{
		*shell_fd = ft_memalloc(sizeof(t_shell_fds));
		(*shell_fd)->fd = add;
	}
	else
	{
		s = *shell_fd;
		while (s->next)
			s = s->next;
		s->next = ft_memalloc(sizeof(t_shell_fds));
		s->next->fd = add;
	}
}

void	free_restored_fd(t_shell_fds *l)
{
	if (l)
	{
		free_restored_fd(l->next);
		free(l);
	}
}

void	free_redirections(t_redirection *r)
{
	if (r)
	{
		free_redirections(r->next);
		if (r->here_doc_eof)
			free(r->here_doc_eof);
		if (r->redirector.filename)
			free(r->redirector.filename);
		if (r->redirector.hereword)
			free(r->redirector.hereword);
		if (r->redirectee.filename)
			free(r->redirectee.filename);
		if (r->redirectee.hereword)
			free(r->redirectee.hereword);
		free(r);
	}
}
