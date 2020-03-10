/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:20:25 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 19:15:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	fill_line(char value, char *user_input, char *hist_proposal, int mode)
{
	int	user_len;
	int	hist_len;
	int	cursor_pos;

	ft_bzero(g_line.line, g_line.size_buf);
	clear_line();
	user_len = ft_strlen(user_input);
	hist_len = ft_strlen(hist_proposal);
	if (user_len >= 1 && value != 127)
		user_len--;
	if (user_input && mode)
		insert_text(user_input, user_len);
	cursor_pos = g_dis.cbpos;
	if (mode)
		insert_text("' : ", 4);
	insert_text(hist_proposal, hist_len);
	g_dis.cbpos = cursor_pos;
	update_line();
	free(hist_proposal);
	if (mode)
		free(user_input);
}

char	*get_input_proposal(char value, char **user_input, char **hist_proposal)
{
	char	*tmp;
	char	buf[2];

	buf[0] = value;
	buf[1] = '\0';
	tmp = g_line.line + g_dis.cbpos;
	*tmp = '\0';
	if (value == 127)
		*user_input = ft_strdup(g_line.line);
	else if (isprintchr(value))
		*user_input = ft_strjoin(g_line.line, buf);
	else
		*user_input = tmp;
	*hist_proposal = ft_strdup(tmp + 4);
	if (!*user_input || !*hist_proposal)
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (NULL);
	}
	return (tmp);
}

void	prepare_hist_lookup(char **original_prompt)
{
	char	*hist_proposal;

	hist_proposal = NULL;
	if (!(*original_prompt = ft_strdup(g_dis.prompt)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	g_hist_lookup = 1;
	set_prompt("(reverse-i-search)`");
	if (!(hist_proposal = ft_strdup(g_line.line)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	fill_line(127, NULL, hist_proposal, 1);
}

void	add_new_proposal(char value, char *user_input, char *hist_proposal)
{
	char		*tmp;

	tmp = hist_proposal;
	if (value == 127 && ft_strlen(user_input) > 0)
		user_input[ft_strlen(user_input) - 1] = '\0';
	if (!(get_matching_hist(&tmp, user_input)))
		set_prompt("(failed reverse-i-search)`");
	else if (ft_strequ(g_dis.prompt, "(failed reverse-i-search)`"))
		set_prompt("(reverse-i-search)`");
	if (value == 127)
		user_input[ft_strlen(user_input)] = 'p';
	if (!(tmp = ft_strdup(tmp)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	free(hist_proposal);
	fill_line(value, user_input, tmp, 1);
}

void	hist_lookup(union u_buffer c)
{
	static char	*original_prompt = NULL;
	char		*user_input;
	char		*hist_proposal;

	user_input = NULL;
	hist_proposal = NULL;
	if (!g_hist_lookup)
	{
		prepare_hist_lookup(&original_prompt);
		return ;
	}
	if (!(get_input_proposal(c.value, &user_input, &hist_proposal)))
		return ;
	if (!isprintchr(c.value) && c.value != 127)
	{
		set_prompt(original_prompt);
		free(original_prompt);
		original_prompt = NULL;
		g_hist_lookup = 0;
		fill_line(c.value, user_input, hist_proposal, 0);
		return ;
	}
	add_new_proposal(c.value, user_input, hist_proposal);
}
