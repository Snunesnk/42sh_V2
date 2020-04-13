/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:32:50 by efischer          #+#    #+#             */
/*   Updated: 2020/04/13 14:11:06 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

static int		match_name(char *var_name, char **name)
{
	int		ret;
	int		i;

	i = 0;
	ret = FALSE;
	while (name[i])
	{
		if (ft_strequ(var_name, name[i]) == TRUE)
		{
			ret = TRUE;
			break ;
		}
		i++;
	}
	return (ret);
}

static void		unset_var(char **args)
{
	extern t_list	*g_env;
	t_list			*head;
	t_list			*tmp;

	head = g_env;
	tmp = g_env;
	g_env = g_env->next;
	while (g_env != NULL)
	{
		if (match_name(((t_shell_var*)(g_env->content))->name, args) == TRUE)
		{
			tmp->next = g_env->next;
			ft_lstdelone(&g_env, &del_elem);
			g_env = tmp->next;
		}
		else
		{
			tmp = g_env;
			g_env = g_env->next;
		}
	}
	g_env = head;
}

int				cmd_unset(int ac, char **av)
{
	int		ret;
	char	**args;
	int		option;

	option = 1;
	args = av + 1;
	if (ac > 1 && (ret = get_next_opt(&args, "v")) != -1)
	{
		if (ret != 'v')
		{
			ft_dprintf(STDERR_FILENO, "./21sh: unset: -%c: invalid option\n", \
					ret);
			ft_putendl_fd("unset: usage: unset [-v] [arg ...]", 2);
			return (e_invalid_input);
		}
		option++;
	}
	if (args)
		unset_var(args);
	return (e_success);
}
