/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:48:52 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/05 18:55:46 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

static char		*create_new_line(char *str, int *len)
{
	char	*new_line;

	new_line = (char*)ft_memalloc(*len + 2);
	if (!new_line)
	{
		*len = -1;
		return (NULL);
	}
	else
	{
		if (str)
		{
			new_line = ft_strncpy(new_line, str, *len + 1);
			free(str);
		}
		return (new_line);
	}
}

static int		get_block(int fd, char **line, int len, char separator)
{
	int		ret;
	char	c;

	ret = 0;
	while (ret < len)
	{
		c = ft_getch_fd(fd);
		if (c == -1 && **line)
			c = separator;
		else if (c == -1)
			return (-2);
		if (c == separator || !c)
		{
			(*line)[ret] = 0;
			return (ret);
		}
		(*line)[ret] = c;
		++ret;
	}
	if (ret == len)
		return (-1);
	else
		return (1);
}

int				get_stdin(int fd, char **line)
{
	int		len;
	int		ret;
	char	*new_line;

	len = 0;
	ret = 0;
	new_line = NULL;
	while (1)
	{
		len += 128;
		new_line = create_new_line(new_line, &len);
		if (len == -1 || !new_line)
			return (-1);
		*line = new_line;
		if ((ret = get_block(fd, line, len, '\n')) == -1)
			continue ;
		if (ret == -2)
		{
			ft_memdel((void**)line);
			return (-1);
		}
		else
			return (1);
	}
	return (ret);
}

char		*append_line(char **last_lines, char *input)
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
	if (input && (qmode = get_str_qmode(NO_QUOTE, input)) != NO_QUOTE)
	{
		if (qmode & BSQUOTE)
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

char			*get_input(const char *prompt, int close_quotes)
{
	char	*input;
	int		first_iter;
	char	*last_lines;

	input = NULL;
	first_iter = 1;
	last_lines = NULL;
	while (first_iter || last_lines)
	{
		if (g_shell_is_interactive)
			input = ft_readline(first_iter ? prompt : "> ");
		else if (get_stdin(STDIN_FILENO, &input) < 0)
			break ;
		if (input && close_quotes)
			input = append_line(&last_lines, input);
		first_iter = 0;
	}
	if (!input && last_lines)
		input = last_lines;
	else
		ft_memdel((void **)&last_lines);
	return (input);
}
