/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_compl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:00 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:40:01 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_compl(t_node *compl_tree, t_data *data)
{
	char	*compl;
	size_t	len;

	while (compl_tree && data->chosen_exec != compl_tree->nb_node)
	{
		if (data->chosen_exec > compl_tree->nb_node)
			compl_tree = compl_tree->right;
		else
			compl_tree = compl_tree->left;
	}
	compl = compl_tree->name;
	len = ft_strlen(compl);
	while (g_dis.cbpos > 0 && !ft_isspace(g_line.line[g_dis.cbpos - 1] \
				&& g_line.line[g_dis.cbpos] != '/'))
		rl_backspace();
	insert_text(compl, len);
}
