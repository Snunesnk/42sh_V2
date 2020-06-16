/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_s_opt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:33:44 by snunes            #+#    #+#             */
/*   Updated: 2020/06/16 12:59:55 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_sub	*init_sub(t_sub *prev_sub)
{
	t_sub	*new_sub;

	if (!(new_sub = (t_sub *)ft_memalloc(sizeof(t_sub))))
	{
		pbierror("cannot allocate memory");
		return (NULL);
	}
	new_sub->next = NULL;
	new_sub->prev = prev_sub;
	new_sub->pat = NULL;
	new_sub->rep = NULL;
	return (new_sub);
}

t_sub	*fill_sub(t_sub *sub_list, char *pat, char *rep)
{
	if (!pat || !rep)
		return (sub_list);
	if (!(sub_list->pat = ft_strdup(pat)) \
			|| !(sub_list->rep = ft_strdup(rep)))
	{
		pbierror("cannot allocate memory");
		return (NULL);
	}
	return (sub_list);
}

char	*fc_do_substitute(int nb_cmd, t_sub *sub_list)
{
	char	*new_cmd;
	char	*str;

	while (nb_cmd < g_hist.nb_line && g_hist.nb_line > 1)
		prev_hist();
	str = g_hist.history_content + g_hist.offset + 1;
	if (!(new_cmd = ft_strdup(str)))
	{
		pbierror("cannot allocate memory");
		return (NULL);
	}
	while (sub_list && sub_list->pat && sub_list->rep)
	{
		if (!(new_cmd = ft_strreplace(&new_cmd, sub_list->pat, sub_list->rep)))
		{
			pbierror("cannot allocate memory");
			return (NULL);
		}
		sub_list = sub_list->next;
	}
	return (new_cmd);
}

int		get_subs(t_sub **sub_list, char ***args)
{
	char	*tmp;

	while (**args && (tmp = ft_strchr(**args, '=')))
	{
		*tmp = '\0';
		tmp += 1;
		if (!(*sub_list = fill_sub(*sub_list, **args, tmp)))
			return (e_cannot_allocate_memory);
		if (!((*sub_list)->next = init_sub(*sub_list)))
			return (e_cannot_allocate_memory);
		*sub_list = (*sub_list)->next;
		*args += 1;
	}
	while ((*sub_list)->prev)
		*sub_list = (*sub_list)->prev;
	return (e_success);
}

int		exec_fc_s_opt(char **args)
{
	char	*tmp;
	t_sub	*sub_list;
	int		nb_cmd;

	nb_cmd = -1;
	sub_list = NULL;
	if (!(sub_list = init_sub(NULL)))
		return (e_cannot_allocate_memory);
	tmp = prev_hist();
	if (get_subs(&sub_list, &args) == e_cannot_allocate_memory)
		return (e_cannot_allocate_memory);
	get_hist_num(args, NULL, NULL, &nb_cmd);
	if (nb_cmd == -1)
	{
		pbierror("no command found");
		free_substitute(sub_list);
		return (e_command_not_found);
	}
	if (!(tmp = fc_do_substitute(nb_cmd, sub_list)))
		return (e_cannot_allocate_memory);
	free_substitute(sub_list);
	ft_dprintf(STDERR_FILENO, "%s\n", tmp);
	add_hentry(tmp, ft_strlen(tmp));
	return (exec_input(tmp, STDOUT_FILENO));
}
/*
** In case fc takes "cat << EOF" in batch mode, we were not sure fc would takes
** heredoc input from STDIN or on the same fd used by batch mode.
*/
