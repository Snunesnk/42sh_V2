#include "libft.h"
#include "shell.h"

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

int			cmd_unset(int ac, char **av)
{
	extern t_list	*g_env;
	t_list			*head;
	t_list			
	int				ret;
	char			**name;
	size_t			i;

	ret = SUCCESS;
	head = g_env;
	if (ft_getopt(ac - 1, av, "") == FALSE)
	{
		ft_putendl_fd("unset: usage: unset [arg ...]", 2);
		ret = FAILURE;
	}
	name = get_name_tab(ac - 1, av + 1);
	if (name != NULL)
	{
		while (g_env != NULL)
		{
			i = 0;
			while (name[i] != NULL)
			{
				if (ft_strequ(((t_shell_var*)(g_env->content))->name, name[i])
						== TRUE)
				{
					ft_lstdelone(&g_env, &del_elem);
					break ;
				}
				i++;
			}
			if (g_env != NULL)
				g_env = g_env->next;
		}
	}
	ft_free_tab(name);
	g_env = head;
	return (ret);
}
