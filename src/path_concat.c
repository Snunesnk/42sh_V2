/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_concat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/21 13:59:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	remove_doubleslash(char *str)
{
	char	*ptr;

	while ((ptr = ft_strstr(str, "//")))
	{
		ft_memmove(ptr, (ptr + 1), ft_strlen((ptr + 1)));
		while (*(ptr + 1))
			++ptr;
		while (*ptr)
		{
			*ptr = '\0';
			++ptr;
		}
	}
}

static void	currentdir_trim(char *str)
{
	char	*ptr;
	int		l;

	while (!ft_strncmp(str, "./", 2))
	{
		l = ft_strlen(str + 2);
		ft_memmove(str, str + 2, l);
		str[l] = '\0';
	}
	ptr = str;
	while ((ptr = ft_strstr(ptr, "/./")))
	{
		l = ft_strlen(ptr + 2);
		ft_memmove(ptr, ptr + 2, l);
		ptr[l] = '\0';
	}
	if (*str)
	{
		l = ft_strlen(str);
		if ((l >= 2 && !ft_strncmp(&str[l - 2], "/.", 2))
			|| !ft_strcmp(str, "."))
			str[l - 1] = '\0';
	}
}

char		*fullpath_concat(char *dir)
{
	char	*path;
	char	*wd;

	wd = getcwd(NULL, 0);
	path = ft_strnjoin(3, wd, "/", dir);
	free(wd);
	free(dir);
	wd = get_shell_var("PATH", g_env);
	if (!wd || !*wd)
		currentdir_trim(path);
	remove_doubleslash(path);
	return (path);
}

int			path_concat(char **bin, char *beg, char *env, char *dir)
{
	char	*pathname;

	beg = get_shell_var("PATH", g_env);
	if (!beg || !*beg)
		env = ft_strdup(".");
	else
		env = ft_strdup(beg);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		pathname = ft_strnjoin(3, dir, "/", *bin);
		if (!access(pathname, F_OK))
			break ;
		ft_memdel((void**)&pathname);
	}
	ft_memdel((void**)&beg);
	ft_memdel((void**)bin);
	if (dir)
	{
		*bin = pathname;
		return (e_success);
	}
	return (e_command_not_found);
}
