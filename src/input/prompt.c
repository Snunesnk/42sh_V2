/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:38:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:36:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "path.h"

static int	print_ifstatus(int status, char **pwd)
{
	int	ret;

	if (*g_pwd)
	{
		ret = ft_printf(
			"\e[1m\e[38;5;14m%s \e[0m\e[38;5;160m⦗%d⦘ ➠ \e[0m",
			short_logical_path(pwd), status);
	}
	else
	{
		ret = ft_printf(
			"\e[1m\e[38;5;14m%s \e[0m\e[38;5;160m⦗%d⦘ ➠ \e[0m",
			short_physical_path(pwd), status);
		ft_memdel((void**)pwd);
	}
	return (ret);
}

static int	print_stdprompt(char **pwd)
{
	int	ret;

	if (*g_pwd)
	{
		ret = ft_printf("\e[1m\e[38;5;14m%s\e[0m\e[38;5;82m ➠ \e[0m",
				short_logical_path(pwd));
	}
	else
	{
		ret = ft_printf("\e[1m\e[38;5;14m%s\e[0m\e[38;5;82m ➠ \e[0m",
				short_physical_path(pwd));
		ft_memdel((void**)pwd);
	}
	return (ret);
}

_Bool	prompt_display(int status)
{
	int		ret;
	char	*pwd;

	if (status)
		ret = print_ifstatus(status, &pwd);
	else
		ret = print_stdprompt(&pwd);
	return (ret);
}
