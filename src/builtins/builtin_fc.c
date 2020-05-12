/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/05/12 14:51:05 by snunes           ###   ########.fr       */
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
			if (ft_isprint(opt))
				fc_invalid_input(**args, opt);
			return (2);
		}
	}
	return (opt_list);
}

int			cmd_fc(int argc, char **argv)
{
	char	**args;
	int		opt_list;
	int		status;
	char	*tmp;

	(void)argc;
	args = argv + 1;
	if ((opt_list = parse_fc_option(&args)) == 2)
		return (e_invalid_input);
	if (!g_shell_is_interactive)
		return (1);
	tmp = ft_strdup(prev_hist());
	fc_erase_last_hist();
	if (g_needed_arg && g_needed_arg[0] == '-' && g_needed_arg[1] == '\0')
		opt_list |= FC_S_OPTION;
	status = (opt_list & FC_S_OPTION) ? exec_fc_s_opt(args) \
			: exec_fc_other_opt(opt_list, args);
	if ((opt_list & FC_L_OPTION) && !g_hist.hist_ignore)
		add_hentry(tmp, ft_strlen(tmp));
	free(tmp);
	if (g_needed_arg)
		g_needed_arg = NULL;
	return (status);
}
