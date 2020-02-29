/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:30:44 by snunes            #+#    #+#             */
/*   Updated: 2020/02/29 18:37:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_hashed_targets_util(t_hash_table *tmp, int l_option, \
		char *arg, int multiple)
{
	if (l_option)
		ft_printf("builtin hash -p %s %s\n", tmp->command_path, arg);
	else
	{
		if (multiple)
			ft_printf("%s\t", arg);
		ft_printf("%s\n", tmp->command_path);
		tmp->nb_called += 1;
	}
}

void	print_hashed_commands_util(t_hash_table *tmp, int l_option)
{
	if (l_option)
	{
		while (tmp)
		{
			ft_printf("builtin hash -p %s %s\n", tmp->command_path, \
					tmp->command_name);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			ft_printf("%4d\t%s\n", tmp->nb_called, tmp->command_path);
			tmp = tmp->next;
		}
	}
}

char	deal_with_p_opt(char ***args, int *x)
{
	if (!(**args)[*x + 1] && !(*args)[1])
	{
		print_error(0, "", 0);
		get_next_opt(NULL);
		return (e_invalid_input);
	}
	else if (!(**args)[*x + 1])
	{
		g_pathname = *(*args + 1);
		*args += 2;
		*x = 0;
	}
	else
	{
		g_pathname = **args + *x + 1;
		*args += 1;
		*x = 0;
	}
	return ('p');
}

char	return_next_opt(char ***args, int *x)
{
	static char	options_list[] = "dlprt";

	if ((**args)[1] == '-' && !(**args)[2])
	{
		(*args)++;
		return (get_next_opt(NULL));
	}
	if (ft_strchr(options_list, (**args)[*x]))
	{
		if ((**args)[*x] == 'p')
			return (deal_with_p_opt(args, x));
		return ((**args)[*x]);
	}
	print_error(1, &((**args)[*x]), 0);
	get_next_opt(NULL);
	return (e_invalid_input);
}
