/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_great2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:03:00 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 18:33:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

t_redirection	*type_andgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	(void)io_nb;
	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->instruction = IODUP | IOWRITE;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	expand_filename(r);
	(*lst) = (*lst)->next;
	return (r);
}
