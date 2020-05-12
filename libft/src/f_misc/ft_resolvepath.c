/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolvepath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:47:47 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/12 14:56:49 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_errno.h"
#include "libft.h"

static void	clean_end(char *str)
{
	char	*beg;

	beg = str;
	while (*str)
		++str;
	if ((str - beg) > 1)
	{
		if (str[-1] == '/')
			str[-1] = '\0';
	}
	else if ((str - beg) == 0)
	{
		*str = '/';
		*(str + 1) = '\0';
	}
}

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
	int	l;

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

static void	previousdir_res(char *str)
{
	char	*ptr;
	char	*next;
	int		i;

	i = 0;
	while ((ptr = ft_strstr(str, "..")))
	{
		next = ptr + 2;
		ptr -= 2;
		while (ptr > str && *ptr != '/')
			--ptr;
		if (ptr < str)
			ptr = str;
		i = ft_strlen(next);
		ft_memmove(ptr, next, i + 1);
	}
}

char		*ft_resolvepath(char *str)
{
	if (!str || *str != '/')
	{
		g_errno = E_EINVAL;
		return (str);
	}
	if (ft_strstr(str, "..."))
	{
		g_errno = E_ENOENT;
		return (str);
	}
	remove_doubleslash(str);
	currentdir_trim(str);
	previousdir_res(str);
	remove_doubleslash(str);
	clean_end(str);
	return (str);
}
