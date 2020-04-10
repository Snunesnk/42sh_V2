/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:03:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 15:03:52 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	name_shvar_cmp(void *str_ref, void *shvar_ptr)
{
	char	*name;

	name = ((t_shell_var *)shvar_ptr)->name;
	return (ft_strcmp((char *)str_ref, name));
}

static char	**unalias_opt(int argc, char **argv)
{
	int	opt;
	int	unset_all;

	unset_all = 0;
	g_opterr = 1;
	g_optind = 1;
	while ((opt = ft_getopt(argc, argv, "a")) != -1)
	{
		if (opt == 'a')
			unset_all = 1;
		else if (opt == '?')
			return (NULL);
	}
	if (unset_all)
		ft_lstdel(&g_alias, del_env);
	return (argv + g_optind);
}

static int	remove_alias(t_list **lst, void *content_ref)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	if (!lst || !*lst)
		return (FAILURE);
	prev = NULL;
	cur = *lst;
	next = cur ? cur->next : NULL;
	while (cur)
	{
		if (!name_shvar_cmp(content_ref, cur->content))
		{
			ft_lstdelone(&cur, del_env);
			if (prev)
				prev->next = next;
			else
				*lst = next;
			return (SUCCESS);
		}
		prev = cur ? cur : prev;
		cur = next;
		next = cur ? cur->next : next;
	}
	return (FAILURE);
}

int			cmd_unalias(int argc, char **argv)
{
	int			ret;

	ret = FAILURE;
	if (argc == 1)
		ft_putstr_fd("unalias: no argument\n", 2);
	else
	{
		ret = SUCCESS;
		if (!(argv = unalias_opt(argc, argv)))
			return (FAILURE);
		while (*argv)
		{
			if (remove_alias(&g_alias, *argv) == FAILURE)
			{
				ft_dprintf(2, "unalias: %s: not found\n", *argv);
				ret = FAILURE;
			}
			++argv;
		}
	}
	return (ret);
}
