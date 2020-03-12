/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/12 10:01:07 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			is_redir_type(int type)
{
	return (type == GREATAND
		|| type == LESSAND
		|| type == ANDGREAT
		|| type == DGREAT
		|| type == DLESS
		|| type == GREAT
		|| type == LESS);
}

char		*get_tokvalue(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->value);
}

int			get_tokentype(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->type);
}

static int	test_lst(t_token **t, t_list **lst, int *argc)
{
	if (*lst)
	{
		*t = (*lst)->content;
		if ((*t)->type == WORD)
		{
			++(*argc);
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

int			get_argc(t_list *lst, int argc, t_token *t)
{
	while (lst)
	{
		t = lst->content;
		if (t->type == WORD)
			++argc;
		else if (t->type == IO_NB)
		{
			lst = lst->next->next->next;
			if (test_lst(&t, &lst, &argc))
				continue;
		}
		else if (is_redir_type(t->type))
		{
			lst = lst->next->next;
			if (test_lst(&t, &lst, &argc))
				continue;
		}
		else
			break ;
		if (lst)
			lst = lst->next;
		else
			break ;
	}
	return (argc);
}
