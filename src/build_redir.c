/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 16:16:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static t_redirection	*parse_redirection(t_list **lst)
{
	int		io_nb;

	if (get_tokentype(*lst) == IO_NB)
	{
		io_nb = ft_atoifd(get_tokvalue(*lst));
		(*lst) = (*lst)->next;
	}
	else
		io_nb = -1;
	return (set_redirection(lst, io_nb));
}

static t_redirection	*build_redirections_suite(t_list **lst,
											t_redirection *r)
{
	t_redirection	**n;

	if (r)
		n = &(r->next);
	while (*lst && get_tokentype(*lst) != PIPE)
	{
		while (*lst && get_tokentype(*lst) != PIPE
		&& get_tokentype(*lst) != IO_NB && !is_redir_type(get_tokentype(*lst)))
			(*lst) = (*lst)->next;
		if (*lst && (get_tokentype(*lst) == IO_NB
					|| is_redir_type(get_tokentype(*lst))))
		{
			while (*lst && has_redirections(get_tokentype(*lst)))
			{
				*n = parse_redirection(lst);
				if (*n)
					n = &((*n)->next);
			}
		}
	}
	return (r);
}

t_redirection			*build_redirections(t_list **lst)
{
	t_redirection	*r;

	while (*lst && get_tokentype(*lst) != PIPE
		&& get_tokentype(*lst) != IO_NB && !is_redir_type(get_tokentype(*lst)))
		(*lst) = (*lst)->next;
	if (*lst)
		r = parse_redirection(lst);
	else
		return (NULL);
	return (build_redirections_suite(lst, r));
}
