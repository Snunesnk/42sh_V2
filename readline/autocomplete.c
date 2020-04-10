/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:36:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 23:00:37 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	g_autocompl_on = 0;

void	command_complete(char *to_complete)
{
	char	*path;
	t_node	*compl_tree;
	t_data	*data;

	if (!(data = init_data()))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	if (!(path = ft_strdup(getenv("PATH"))))
	{
		if (!getenv("PATH"))
			ft_dprintf(STDERR_FILENO, "./21sh: PATH not set.\n");
		else
			ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	if (!(compl_tree = get_cmd_compl(to_complete, path, data)))
		return ;
	display_compl(compl_tree, data);
	free(data);
	free(path);
	free_node(compl_tree);
}

void	var_complete(char *to_complete)
{
	ft_printf("\nI should complete %s with an env var\n", to_complete);
}

void	file_complete(char *to_complete)
{
	t_node	*compl_tree;
	t_data	*data;

	if (!(data = init_data()))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	if (!(compl_tree = get_file_compl(to_complete, data)))
		return ;
	display_compl(compl_tree, data);
	free(data);
	free_node(compl_tree);
}

void	autocomplete(void)
{
	char	*to_complete;
	int		i;

	g_autocompl_on = 1;
	i = g_dis.cbpos - 1;
	while (i >= 0 && !ft_isspace(g_line.line[i]))
		i--;
	to_complete = ft_strsub(g_line.line, i + 1, g_dis.cbpos - i + 1);
	if (ft_strchr(to_complete, '/'))
		file_complete(to_complete);
	else if (g_line.line[i + 1] == '$')
		var_complete(to_complete);
	else if (i <= 0)
		command_complete(to_complete);
	else
		file_complete(to_complete);
	g_autocompl_on = 0;
	free(to_complete);
}
