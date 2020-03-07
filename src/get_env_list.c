/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:03:26 by efischer          #+#    #+#             */
/*   Updated: 2020/03/07 16:09:28 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

extern t_list	*g_env;

void	del_env(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_shell_var*)(content))->name);
	ft_strdel(&((t_shell_var*)(content))->value);
	free(content);
}

void	alpha_sort(t_list **lst1, t_list **lst2, t_list **head)
{
	if (ft_strcmp(((t_shell_var*)((*lst1)->content))->name,
	((t_shell_var*)((*lst2)->content))->name) > 0)
	{
		*head = *lst2;
		*lst2 = (*lst2)->next;
	}
	else
	{
		*head = *lst1;
		*lst1 = (*lst1)->next;
	}
}

void	print_env(t_list *env, t_list **elem)
{
	char	*tmp;

	tmp = NULL;
	if (((t_shell_var*)(env->content))->value == NULL)
		ft_asprintf(&tmp, "%s\n", ((t_shell_var*)(env->content))->name);
	else
	{
		ft_asprintf(&tmp, "%s=%s\n", ((t_shell_var*)(env->content))->name,
				((t_shell_var*)(env->content))->value);
	}
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
}

int		get_env_list(char **environ)
{
	t_shell_var	shell_var;
	t_list		*lst_new;
	char		*name;
	char		*value;
	size_t		i;

	i= 0;
	ft_bzero(&shell_var, sizeof(shell_var));
	while (environ[i] != NULL)
	{
		value = ft_strchr(environ[i], '=');
		name = ft_strndup(environ[i], value - environ[i]);
		shell_var.name = name;
		shell_var.value = ft_strdup(value + 1);
		shell_var.flag |= SET;
		shell_var.flag |= EXPORT;
		lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
		if (lst_new == NULL)
			return (EXIT_FAILURE);
		ft_lstadd(&g_env, lst_new);
		i++;
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (EXIT_SUCCESS);
}
