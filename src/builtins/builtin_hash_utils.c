/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:30:44 by snunes            #+#    #+#             */
/*   Updated: 2020/06/12 15:14:51 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*g_builtin_name = NULL;

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

char	deal_with_spe_opt(char ***args, int *x)
{
	int	spe;

	spe = (**args)[*x];
	if (!(**args)[*x + 1] && !(*args)[1])
	{
		pbierror("-%c: option requires an argument", spe);
		get_next_opt(NULL, NULL);
		return (e_invalid_input);
	}
	else if (!(**args)[*x + 1])
	{
		g_needed_arg = *(*args + 1);
		*args += 2;
		*x = 0;
	}
	else
	{
		g_needed_arg = **args + *x + 1;
		*args += 1;
		*x = 0;
	}
	get_next_opt(NULL, NULL);
	return (spe);
}

char	return_next_opt(char ***args, int *x, const char *options_list)
{
	char	*tmp;
	int		ret;

	if ((**args)[1] == '-' && !(**args)[2])
	{
		(*args)++;
		return (get_next_opt(NULL, NULL));
	}
	if ((tmp = ft_strchr(options_list, (**args)[*x])))
	{
		if (*tmp && *(tmp + 1) == ':')
			return (deal_with_spe_opt(args, x));
		return ((**args)[*x]);
	}
	ret = *x;
	get_next_opt(NULL, NULL);
	return ((**args)[ret]);
}

void	print_error(char *usage, char option, int mode)
{
	if (mode & 1)
		pbierror("-%c: invalid option", option);
	if (mode & 2)
		pbierror("usage: %s %s", g_builtin_name, usage);
}
