/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_compl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:00 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 14:45:33 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_compl(t_node *compl_tree, t_data *data, long int c)
{
	char		*compl;
	size_t		len;
	static char	operator[] = "&|<>;";

	while (compl_tree && data->chosen_exec != compl_tree->nb_node)
	{
		if (data->chosen_exec > compl_tree->nb_node)
			compl_tree = compl_tree->right;
		else
			compl_tree = compl_tree->left;
	}
	compl = compl_tree->name;
	len = ft_str_wchar_len(compl);
	while (g_line.line[g_line.c_pos] && g_line.line[g_line.c_pos] != ' ' \
			&& !ft_strchr(operator, g_line.line[g_line.c_pos]))
		rl_delete();
	if (g_line.line[g_line.c_pos] == '/')
		rl_delete();
	while (g_line.c_pos > data->compl_start)
		rl_backspace();
	insert_text(compl, len);
	if (c == '\n' && g_line.line[g_line.c_pos] != '/')
		insert_text(" ", 1);
}
