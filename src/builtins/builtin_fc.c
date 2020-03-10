/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 21:41:30 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	parse_fc_option(char ***args)
{
	int	opt;
	int	opt_list;

	opt_list = 0;
	while ((opt = get_next_opt(args, "e:lnrs")) != -1)
	{
		if (opt == 'n')
			opt_list |= FC_N_OPTION;
		else if (opt == 'l')
			opt_list |= FC_L_OPTION;
		else if (opt == 'r')
			opt_list |= FC_R_OPTION;
		else if (opt == 's')
			opt_list |= FC_S_OPTION;
		else if (opt == 'e')
			opt_list |= FC_E_OPTION;
		else
		{
			if (fc_invalid_input(**args))
				return (2);
			break ;
		}
	}
	return (opt_list);
}

int			cmd_fc(int argc, char **argv)
{
	char	**args;
	int		opt_list;
	int		status;

	(void)argc;
	if (!argv)
		return (e_invalid_input);
	args = argv + 1;
	g_builtin_name = argv[0];
	if ((opt_list = parse_fc_option(&args)) == 2)
		return (e_invalid_input);
	if (g_needed_arg && g_needed_arg[0] == '-' && g_needed_arg[1] == '\0')
		opt_list |= FC_S_OPTION;
	if (opt_list & FC_S_OPTION)
		status = exec_fc_s_opt(args);
	else
		status = exec_fc_other_opt(opt_list, args);
	return (status);
}
