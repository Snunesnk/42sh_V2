/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:56:23 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/22 13:06:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "builtins.h"

char	*g_progname;

const struct s_error_desc	g_errordesc[] =
{
	{ 0, "no error" },
	{ 0, "warning: here-document delimited by end-of-file (wanted `EOF')" },
	{ 1, "invalid input" },
	{ 1, "no such builtin" },
	{ 1, "bad substitution" },
	{ 1, "cannot assign list to array member" },
	{ 1, "ambiguous redirect" },
	{ 1, "Bad file descriptor" },
	{ 1, "no job control"},
	{ 1, "no such file or directory"},
	{ 1, "permission denied" },
	{ 2, "syntax error near unexpected token" },
	{ 2, "syntax error: unexpected end of file" },
	{ 2, "filename argument required\n.: usage: . filename [arguments]" },
	{ 2, "cannot allocate memory" },
	{ 2, "system call error" },
	{ 126, "permission denied" },
	{ 126, "is a directory" },
	{ 126, "Too many levels of symbolic links" },
	{ 127, "command not found" },
	{ 127, "no such file or directory" },
	{ 128, "resource temporarily unavailable" },
	{ 130, "input interrupted by signal" },
	{ 130, "syntax error: unexpected end of file" }
};

int	psherror(int e_error, char *str, int e_message_type)
{
	if (e_message_type == e_parsing_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s \'%s\'\n", \
				g_progname, g_errordesc[e_error].message, str);
	}
	else if (e_message_type == e_cmd_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
				g_progname, str, g_errordesc[e_error].message);
	}
	else if (e_message_type == e_invalid_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", \
				g_progname, g_errordesc[e_error].message);
	}
	return (e_error);
}

int	pbierror(const char *err_fmt, ...)
{
	va_list	ap;
	int		ret;

	ret = ft_dprintf(STDERR_FILENO, "%s: %s: ", g_progname, g_builtin_name);
	va_start(ap, err_fmt);
	ret += ft_vdprintf(STDERR_FILENO, err_fmt, ap);
	va_end(ap);
	ret += write(STDERR_FILENO, "\n", 1);
	return (ret);
}
