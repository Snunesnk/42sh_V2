/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:33:28 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 13:29:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

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
