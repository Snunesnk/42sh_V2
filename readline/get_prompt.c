/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 21:10:46 by snunes            #+#    #+#             */
/*   Updated: 2020/04/16 15:40:23 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "shell.h"

size_t		get_vis_prompt_len(char *prompt)
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

static int	remove_home(char **pwd)
{
	char	*home;
	char	*tmp;

	if (!(home = get_shell_var_value("HOME", g_env)))
		return (e_success);
	if (!(tmp = ft_strstr(*pwd, home)))
		return (e_success);
	if (!(*pwd = ft_strdup(*pwd)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (e_cannot_allocate_memory);
	}
	tmp = ft_strstr(*pwd, home);
	tmp[0] = '\0';
	tmp = ft_strcat(tmp, tmp + ft_strlen(home) - 1);
	tmp[0] = '~';
	if (!tmp[1])
	{
		tmp[1] = 0;
		tmp[2] = 0;
	}
	return (e_success);
}

char		*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	int		len;

	if (!(pwd = get_shell_var_value("PWD", g_env)))
		return (ft_strdup("21sh$ "));
	len = ft_strlen(pwd) + ft_strlen(GREEN_ARROW) + ft_strlen(PROMPT_COLOR) \
		+ ft_strlen(END_SIGN) + 1;
	if (!(prompt = (char *)ft_memalloc(sizeof(char) * (len + 1))))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (NULL);
	}
	if (g_retval)
		ft_strcat(prompt, RED_ARROW);
	else
		ft_strcat(prompt, GREEN_ARROW);
	ft_strcat(prompt, PROMPT_COLOR);
	if (remove_home(&pwd))
		return (NULL);
	ft_strcat(prompt, pwd);
	if (!ft_strequ(pwd, get_shell_var_value("PWD", g_env)))
		free(pwd);
	ft_strcat(prompt, END_SIGN);
	return (prompt);
}
