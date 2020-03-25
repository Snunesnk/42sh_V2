#include "libft.h"
#include "shell.h"

static int	add_alias_to_list(char *name, char *value, t_list *elem)
{
	t_shell_var	shell_var;
	t_shell_var	*svar_ptr;
	t_list		*lst_new;

	ft_bzero(&shell_var, sizeof(shell_var));
	if (elem != NULL)
	{
		svar_ptr = (t_shell_var *)elem->content;
		ft_strdel(&svar_ptr->value);
		svar_ptr->value = value;
	}
	else
	{
		shell_var.name = name;
		shell_var.value = value;
		if (!(lst_new = ft_lstnew(&shell_var, sizeof(shell_var))))
		{
			ft_strdel(&name);
			ft_strdel(&value);
			return (FAILURE);
		}
		ft_lstadd(&g_alias, lst_new);
	}
	return (SUCCESS);
}

static char	*get_alias_name(char *str)
{
	char	*delim;

	if (!str || !(delim = ft_strchr(str, '=')) || delim == str)
	{
		if (!str || delim == str)
			ft_putstr_fd("alias: invalid alias name\n", 2);
		else
			ft_putstr_fd("alias: empty alias\n", 2);
		return (NULL);
	}
	return (ft_strndup(str, delim - str));
}

static int	add_alias(char **av)
{
	t_list		*elem;
	char		*name;
	char		*value;

	while (*av != NULL)
	{
		if (!(name = get_alias_name(*av))
			|| !(value = ft_strdup(ft_strchr(*av, '=') + 1)))
		{
			ft_strdel(&name);
			return (FAILURE);
		}
		elem = get_shell_var(name, g_alias);
		if (add_alias_to_list(name, value, elem) == FAILURE)
			return (FAILURE);
		++av;
	}
	ft_merge_sort(&g_alias, &alpha_sort);
	return (SUCCESS);
}

static void	print_alias_list(t_list *lst)
{
	t_shell_var	*svar;

	while (lst)
	{
		svar = (t_shell_var *)lst->content;
		ft_printf("alias %s='%s'\n", svar->name, svar->value);
		lst = lst->next;
	}
}

int		cmd_alias(int argc, char **argv)
{
	if (argc == 1)
		print_alias_list(g_alias);
	else
		return (add_alias(argv + 1));
	return (SUCCESS);
}
