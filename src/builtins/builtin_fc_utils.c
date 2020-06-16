/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:22:01 by snunes            #+#    #+#             */
/*   Updated: 2020/06/16 12:50:19 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	fc_erase_last_hist(void)
{
	while (g_hist.nb_line <= g_hist.total_lines)
		next_hist();
	if (g_hist.hist_ignore)
		return ;
	prev_hist();
	if (g_hist.total_lines <= 1)
	{
		ft_bzero(g_hist.history_content, g_hist.used);
		g_hist.nb_line = 1;
		g_hist.offset = 1;
		g_hist.total_lines = 0;
		g_hist.used = 1;
		return ;
	}
	ft_bzero(g_hist.history_content + g_hist.offset, g_hist.used - \
			g_hist.offset);
	g_hist.used = g_hist.offset + 1;
	g_hist.total_lines = g_hist.nb_line - 1;
}

void	free_substitute(t_sub *substitute)
{
	t_sub	*tmp;

	while (substitute)
	{
		tmp = substitute->next;
		free(substitute->pat);
		free(substitute->rep);
		free(substitute);
		substitute = tmp;
	}
}

char	*ft_strreplace(char **str, char *pattern, char *replacement)
{
	char	*tmp;
	int		found;
	int		pat_len;
	int		rep_len;

	tmp = *str;
	found = 0;
	pat_len = (int)ft_strlen(pattern);
	rep_len = (int)ft_strlen(replacement);
	while (pat_len && (tmp = ft_strstr(tmp, pattern)))
	{
		found++;
		tmp += (pat_len == 0) ? 1 : pat_len;
	}
	if (pat_len < rep_len && !(*str = ft_memrealloc((void **)str, \
		ft_strlen(*str), ft_strlen(*str) + ((rep_len - pat_len) * found) + 1)))
		return (NULL);
	tmp = *str;
	while ((tmp = ft_strstr(tmp, pattern)) || (!pat_len && *(tmp++)))
	{
		ft_memmove(tmp + rep_len, tmp + pat_len, ft_strlen(tmp) - pat_len + 1);
		ft_memmove(tmp, replacement, rep_len);
		tmp += rep_len;
	}
	return (*str);
}

int		fc_invalid_input(char *args, char opt)
{
	int	x;

	x = 0;
	if (ft_str_is_numeric(args + 1))
		return (0);
	while (args[x] && ft_strchr("-elnrs", args[x]))
		x += 1;
	if (opt == 1)
		print_error("[-e ename] [-lnr] [first] [last] or fc -s [pat=rep] "\
				"[command]", args[x], 2);
	else
		print_error("[-e ename] [-lnr] [first] [last] or fc -s [pat=rep] "\
				"[command]", args[x], 3);
	return (e_invalid_input);
}

int		add_pending_cmd(char *command)
{
	t_list	*new_lst;

	if (!command)
		return (0);
	if (!(new_lst = ft_lstnew(command, ft_strlen(command) + 1)))
	{
		pbierror("cannot allocate memory");
		return (0);
	}
	ft_lstaddend(&g_pending_cmd, new_lst);
	return (1);
}
