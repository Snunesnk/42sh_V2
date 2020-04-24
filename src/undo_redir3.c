/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redir3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:33:28 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/24 14:24:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int		undo_redirection(t_redirection *r)
{
	t_shell_fds	*shell_fd;

	shell_fd = NULL;
	if (r)
	{
		undo_redirection_internal(r, &shell_fd);
		free_restored_fd(shell_fd);
	}
	return (0);
}
