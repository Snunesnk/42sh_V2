/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 21:10:46 by snunes            #+#    #+#             */
/*   Updated: 2020/05/12 12:07:18 by snunes           ###   ########.fr       */
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

static char	*remove_home(char *pwd)
{
	char	*home;
	char	*tmp;

	if (!(home = get_shell_var("HOME", g_env)) || !*home)
		return (pwd);
	if (!(tmp = ft_strstr(pwd, home)))
		return (pwd);
	if (access(home, F_OK) || (*(pwd + ft_strlen(home)) != '/' \
				&& !ft_strequ(pwd, home)))
		return (pwd);
	tmp = ft_strstr(pwd, home);
	tmp[0] = '\0';
	tmp = ft_strcat(tmp, tmp + ft_strlen(home) - 1);
	tmp[0] = '~';
	if (!tmp[1])
	{
		tmp[1] = 0;
		tmp[2] = 0;
	}
	return (pwd);
}

static char	*get_dumb_prompt(char *prompt, char *pwd)
{
	if (!(pwd = remove_home(pwd)))
		return (NULL);
	ft_strcat(prompt, pwd);
	ft_strcat(prompt, "$ ");
	return (prompt);
}

static char	*get_normal_prompt(char *prompt, char *pwd)
{
	if (g_retval)
		ft_strcat(prompt, RED_ARROW);
	else
		ft_strcat(prompt, GREEN_ARROW);
	ft_strcat(prompt, PROMPT_COLOR);
	if (!(pwd = remove_home(pwd)))
		return (NULL);
	ft_strcat(prompt, pwd);
	ft_strcat(prompt, END_SIGN);
	return (prompt);
}

char		*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	int		len;

	if (!(pwd = getcwd(NULL, 0)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	if (g_dumb_term)
		len = ft_strlen(pwd) + 3;
	else
		len = ft_strlen(pwd) + ft_strlen(GREEN_ARROW) + \
			ft_strlen(PROMPT_COLOR) + ft_strlen(END_SIGN) + 1;
	if (!(prompt = (char *)ft_memalloc(sizeof(char) * (len + 1))))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	if (g_dumb_term)
		prompt = get_dumb_prompt(prompt, pwd);
	else
		prompt = get_normal_prompt(prompt, pwd);
	free(pwd);
	return (prompt);
}
