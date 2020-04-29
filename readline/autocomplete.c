/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:36:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 14:42:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "shell.h"
#include "error.h"

int	g_autocompl_on = 0;

static t_node	*get_alias_compl(t_node *compl_tree, char *to_complete,
					t_data *data)
{
	t_list	*alias_var;
	char	*alias_name;
	int		pattern_len;

	pattern_len = ft_strlen(to_complete);
	alias_var = g_alias;
	while (alias_var)
	{
		alias_name = ((t_shell_var*)(alias_var->content))->name;
		if (!pattern_len || ft_strnequ(alias_name, to_complete, pattern_len))
			compl_tree = add_node(compl_tree, alias_name, data, "\033[37m");
		alias_var = alias_var->next;
	}
	return (compl_tree);
}

void			command_complete(char *to_complete)
{
	char	*path;
	t_node	*compl_tree;
	t_data	*data;

	if (!(data = init_data()))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	if (!(path = ft_strdup(getenv("PATH"))))
	{
		if (!getenv("PATH"))
			ft_dprintf(STDERR_FILENO, "%s: PATH not set.\n", g_progname);
		else
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	compl_tree = get_cmd_compl(to_complete, path, data);
	compl_tree = get_alias_compl(compl_tree, to_complete, data);
	if (compl_tree)
		display_compl(compl_tree, data);
	free(data);
	free(path);
	free_node(compl_tree);
}

void			var_complete(char *to_complete)
{
	t_node	*compl_tree;
	t_data	*data;
	int		is_bracked;

	is_bracked = 0;
	compl_tree = NULL;
	if (!(data = init_data()))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	if (to_complete[1] == '{')
		is_bracked = 1;
	compl_tree = get_var_compl(to_complete + 1 + is_bracked, data, is_bracked);
	if (compl_tree)
		display_compl(compl_tree, data);
	free(data);
	free_node(compl_tree);
}

void			file_complete(char *to_complete)
{
	int			i;
	t_node		*compl_tree;
	t_data		*data;
	static char	operator[] = "&|;<>";
	int			start;

	start = 0;
	i = 0;
	while (to_complete[i])
	{
		if (ft_strchr(operator, to_complete[i]))
			start = i + 1;
		i++;
	}
	if (!(data = init_data()))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	compl_tree = get_file_compl(to_complete + start, data);
	if (compl_tree)
		display_compl(compl_tree, data);
	free(data);
	free_node(compl_tree);
}

void			autocomplete(void)
{
	char	*to_complete;
	int		start;

	if (g_line.len == 0 || ft_str_isspace(g_line.line))
		return ;
	g_autocompl_on = 1;
	start = g_dis.cbpos - 1;
	while (start >= 0 && !ft_isspace(g_line.line[start]))
		start--;
	to_complete = ft_strsub(g_line.line, start + 1, g_dis.cbpos - start - 1);
	if (ft_strchr(to_complete, '/') || has_operator(to_complete))
		file_complete(to_complete);
	else if (g_line.line[start + 1] == '$')
		var_complete(to_complete);
	else if (start <= 0 || has_no_cmd(g_line.line, start))
		command_complete(to_complete);
	else
		file_complete(to_complete);
	g_autocompl_on = 0;
	free(to_complete);
}
