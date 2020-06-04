/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_complete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:34:21 by snunes            #+#    #+#             */
/*   Updated: 2020/06/04 12:37:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "shell.h"

static char	*get_var_form(char *var_name, int is_bracked)
{
	char	*var_form;

	if (!(var_form = (char *)ft_memalloc(sizeof(char) * \
					(ft_strlen(var_name) + is_bracked + 2))))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	if (is_bracked > 0)
		ft_strcat(var_form, "$");
	if (is_bracked & BRACE)
		ft_strcat(var_form, "{");
	ft_strcat(var_form, var_name);
	if (is_bracked & BRACE)
		ft_strcat(var_form, "}");
	if (is_bracked == 0 && test_cmd("export ", 7))
		ft_strcat(var_form, "=");
	return (var_form);
}

t_node		*get_var_compl(char *to_complete, t_data *data, int is_bracked)
{
	t_node	*compl_tree;
	char	*var_form;
	t_list	*env_var;
	char	*var_name;
	int		pattern_len;

	pattern_len = ft_strlen(to_complete);
	compl_tree = NULL;
	env_var = g_env;
	while (env_var)
	{
		var_name = ((t_shell_var*)(env_var->content))->name;
		if (!pattern_len || ft_strnequ(var_name, to_complete, pattern_len))
		{
			if (!(var_form = get_var_form(var_name, is_bracked)))
				return (compl_tree);
			compl_tree = add_node(compl_tree, var_form, data, "\033[37m");
			free(var_form);
		}
		env_var = env_var->next;
	}
	return (compl_tree);
}
