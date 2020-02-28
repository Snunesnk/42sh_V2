#include "libft.h"
#include "shell.h"

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
	ft_asprintf(&tmp, "%s=%s\n", ((t_shell_var*)(env->content))->name,
			((t_shell_var*)(env->content))->value);
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
}

int		get_env_list(t_list **env, char **environ)
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
		shell_var.flag &= SET;
		shell_var.flag &= EXPORT;
		lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
		if (lst_new == NULL)
			return (FAILURE);
		ft_lstadd(env, lst_new);
		i++;
	}
	ft_merge_sort(env, &alpha_sort);
	return (SUCCESS);
}
