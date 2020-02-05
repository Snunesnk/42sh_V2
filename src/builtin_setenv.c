/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 16:13:05 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static void	print_setenv_syntax_error(t_process *p)
{
	ft_dprintf(p->errfile, "%s: %s: \'%s\': not a valid identifier\n",
					g_progname, p->argv[0], p->argv[1]);
}

static int	is_valid_chr(const char c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		 || (c >= '0' && c <= '9') || c == '_' || c == '/'))
		return (1);
	else
		return (0);
}

static int	has_invalid_syntax(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_valid_chr(str[i]))
			return (e_invalid_input);
		++i;
	}
	return (e_success);
}

int		cmd_setenv(int argc, t_process *p)
{
	if (argc != 3)
	{
		psherror(e_invalid_input, p->argv[0], e_cmd_type);
		ft_dprintf(p->errfile, "Usage: %s VAR [VALUE]\n", p->argv[0]);
		return (g_errordesc[e_invalid_input].code);
	}
	if (has_invalid_syntax(p->argv[1]))
	{
		print_setenv_syntax_error(p);
		return (g_errordesc[e_invalid_input].code);
	}
	else if (has_invalid_syntax(p->argv[2]))
	{
		print_setenv_syntax_error(p);
		return (g_errordesc[e_invalid_input].code);
	}
	else
	{
		if ((ft_setenv(p->argv[1], p->argv[2], 1)))
			return (g_errordesc[e_cannot_allocate_memory].code);
	}
	return (e_success);
}
