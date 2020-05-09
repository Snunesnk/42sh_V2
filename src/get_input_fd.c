/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:58:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/09 14:08:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_input_fd(int fd, int close_quotes, char *prompt)
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
		{
			ft_printf("%s, line:%d, first_iter=%d\n",__FILE__, __LINE__, first_iter); // DEBUGG
			input = ft_readline(first_iter ? prompt : "> ");
		}
		else if (get_stdin(fd, &input) < 0)
			break ;
		if (input && close_quotes)
			input = append_line(&last_lines, input);
		first_iter = 0;
	}
	if (!input && last_lines)
		input = last_lines;
	else
		ft_memdel((void **)&last_lines);
	if (fd == STDIN_FILENO && input && g_shell_is_interactive)
		add_hentry(input, ft_strlen(input));
	return (input);
}
