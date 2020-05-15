/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:03:00 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 19:51:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

t_redirection	*subtype_great_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	expand_filename(r, &r->redirectee.filename);
	(*lst) = (*lst)->next;
	return (r);
}

t_redirection	*type_great_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = subtype_great_redirection(lst, io_nb);
	r->instruction = IOWRITE;
	return (r);
}

t_redirection	*type_dgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = subtype_great_redirection(lst, io_nb);
	r->instruction = IOCAT;
	return (r);
}

t_redirection	*suite_great_and(t_list **lst, t_redirection **r)
{
	if ((*r)->redirectee.filename[0] == '-'
			&& (*r)->redirectee.filename[1] == '\0')
		(*r)->flags |= FDCLOSE;
	else if (ft_str_is_numeric((*r)->redirectee.filename))
	{
		(*r)->redirectee.dest = ft_atoifd((*r)->redirectee.filename);
		(*r)->flags |= DEST;
	}
	else
		(*r)->flags |= FILENAME;
	(*lst) = (*lst)->next;
	return (*r);
}

t_redirection	*type_greatand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	r->instruction = IODUP;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	if (ft_strcmp("-", r->redirectee.filename) && ha(r->redirectee.filename))
	{
		r->error = e_ambiguous_redirect;
		psherror(e_ambiguous_redirect, r->redirectee.filename, e_cmd_type);
		return (r);
	}
	else if (expand_filename(r, &r->redirectee.filename))
		return (r);
	return (suite_great_and(lst, &r));
}
