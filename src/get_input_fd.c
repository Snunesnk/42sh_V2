/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:58:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/27 10:13:08 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "quotes.h"

static char	*append_line(char **last_lines, char *input, int quote_set)
{
	char	*tmp;
	int		qmode;

	if (*last_lines)
	{
		tmp = ft_strjoin(*last_lines, input);
		ft_memdel((void **)last_lines);
		ft_memdel((void **)&input);
		input = tmp;
	}
	if (input && (qmode = get_str_qmode_set(NO_QUOTE, input, quote_set)))
	{
		if ((qmode & BSQUOTE) && (quote_set & BSQUOTE))
		{
			input[ft_strlen(input) - 1] = '\0';
			*last_lines = input;
		}
		else
		{
			*last_lines = ft_strjoin(input, "\n");
			ft_memdel((void **)&input);
		}
		input = NULL;
	}
	return (input);
}

static char	*recup_input(int fd, int quote_set, char *prompt)
{
	char	*input;
	int		first_iter;
	char	*last_lines;

	input = NULL;
	first_iter = 1;
	last_lines = NULL;
	while (first_iter || last_lines)
	{
		if (g_shell_is_interactive && fd == STDIN_FILENO)
			input = ft_readline(first_iter ? prompt : "> ");
		else if (get_stdin(fd, &input) < 0)
			break ;
		if (g_retval == 130)
			break ;
		if (input && quote_set != NO_QUOTE)
			input = append_line(&last_lines, input, quote_set);
		first_iter = 0;
	}
	if (!input && last_lines)
		input = last_lines;
	else
		ft_memdel((void **)&last_lines);
	return (input);
}

char		*get_input_fd(int fd, int quote_set, char *prompt)
{
	char	*input;
	int		ret;

	ret = g_retval;
	if (g_retval)
		g_retval = 1;
	input = recup_input(fd, quote_set, prompt);
	if (fd == STDIN_FILENO && input && g_shell_is_interactive \
			&& quote_set == FULL_QUOTE)
	{
		if (!g_dumb_term)
			add_hentry(input, ft_strlen(input));
	}
	if (g_retval == 1)
		g_retval = ret;
	return (input);
}
