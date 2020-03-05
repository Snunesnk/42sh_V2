#include "libft.h"
#include "shell.h"

static void	ft_free_tab(char **tmp)
{
	int		i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		free(tmp[i]);
		tmp[i++] = NULL;
	}
	free(tmp);
	tmp = NULL;
}

static void	del_elem(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_shell_var*)(content))->name);
	ft_strdel(&((t_shell_var*)(content))->value);
}

static char	**get_name_tab(int ac, char **av)
{
	char	**tab;
	char	*tmp;
	size_t	i;

	i = 0;
	tab = (char**)malloc(sizeof(char*) * (ac + 1));
	if (tab != NULL)
	{
		while (av[i] != NULL)
		{
			tmp = ft_strchr(av[i], '=');
			if (tmp != NULL)
				tab[i] = ft_strndup(av[i], tmp - av[i]);
			else
				tab[i] = ft_strdup(av[i]);
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

static int	match_name(char *var_name, char **name)
{
	int		ret;
	size_t	i;

	i = 0;
	ret = FALSE;
	while (name[i] != NULL)
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

static void	unset_var(char **name)
{
	extern t_list	*g_env;
	t_list			*head;
	t_list			*tmp;

	head = g_env;
	while (g_env != NULL && match_name(((t_shell_var*)(g_env->content))->name, name) == TRUE)
	{
		head = g_env->next;
		ft_lstdelone(&g_env, &del_elem);
		g_env = head;
	}
	tmp = g_env;
	g_env = g_env->next;
	while (g_env != NULL)
	{
		if (match_name(((t_shell_var*)(g_env->content))->name, name) == TRUE)
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

int			cmd_unset(int ac, char **av)
{
	int		ret;
	char	**name;

	ret = SUCCESS;
	if (ft_getopt(ac - 1, av, "") == FALSE)
	{
		ft_putendl_fd("unset: usage: unset [arg ...]", 2);
		ret = FAILURE;
	}
	name = get_name_tab(ac - 1, av + 1);
	if (name != NULL)
		unset_var(name);
	ft_free_tab(name);
	return (ret);
}
