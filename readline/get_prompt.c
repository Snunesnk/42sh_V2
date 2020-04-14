/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 21:10:46 by snunes            #+#    #+#             */
/*   Updated: 2020/04/14 22:58:39 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "shell.h"

size_t	get_vis_prompt_len(char *prompt)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		if (prompt[i] == 27)
		{
			while (prompt[i] != 'm')
				i++;
		}
		else if (prompt[i] < 0)
		{
			while (prompt[i + 1] < 0)
				i++;
			len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*get_prompt(void)
{
	char	*prompt;

	prompt = ft_strdup("\033[38;5;196m\u279c \033[0m");
	if (g_retval)
		write(1, "\033[38;5;196m\u279c \n", sizeof("\033[38;5;196m\u279c" + 1));
	else
		write(1, "\033[38;5;196m\u279c", sizeof("\033[38;5;196m\u279c"));
	//	add_green_arrow
//	add_pwd
//	replace_home
//	and why not short it
	return (prompt);
}
