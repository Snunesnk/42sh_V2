/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:49 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 11:43:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"
#include "builtins.h"

static void	tag_all_redirections(t_redirection *r)
{
	while (r)
	{
		r->flags |= NOFORK;
		r = r->next;
	}
}

int			launch_builtin(t_process *p)
{
	int ret;

	if (p->redir != NULL)
		tag_all_redirections(p->redir);
	if ((ret = do_redirection(p->redir)))
		return (g_errordesc[ret].code);
	ret = builtins_dispatcher(p->argv);
	undo_redirection(p->redir);
	return (ret);
}
