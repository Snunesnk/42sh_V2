/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:36:35 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 19:52:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

t_redirection	*type_less_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IOREAD;
	(*lst) = (*lst)->next;
	r->redirector.filename = ft_strdup(get_tokvalue(*lst));
	expand_filename(r, &r->redirector.filename);
	(*lst) = (*lst)->next;
	return (r);
}

t_redirection	*type_dless_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IOHERE;
	(*lst) = (*lst)->next;
	r->redirector.hereword = ft_strdup(get_tokvalue(*lst));
	(*lst) = (*lst)->next;
	return (r);
}

t_redirection	*type_lessand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IODUP | IOREAD;
	(*lst) = (*lst)->next;
	r->redirector.filename = ft_strdup(get_tokvalue(*lst));
	expand_filename(r, &r->redirector.filename);
	if (r->redirector.filename[0] == '-')
		r->flags |= FDCLOSE;
	else if (ft_str_is_numeric(r->redirector.filename))
	{
		r->redirector.dest = ft_atoifd(r->redirector.filename);
		r->flags |= DEST;
	}
	else
		r->flags |= FILENAME;
	(*lst) = (*lst)->next;
	return (r);
}
