/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:06:23 by snunes            #+#    #+#             */
/*   Updated: 2020/02/29 14:44:33 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

char	*g_pathname = NULL;

int		cmd_hash(int argc, char **argv)
{
	char	**args;
	int		options_list;
	int		status;

	if (argv)
		args = argv + 1;
	else
		args = argv;
//ft_printf("args pointe sur: %s\n", *args);
	options_list = 0;
	while (args && argc > 1 && (status = get_next_opt(&args)) != -1)
	{
		if (status == 'd')
			options_list |= HASH_D_OPTION;
		else if (status == 'l')
			options_list |= HASH_L_OPTION;
		else if (status == 'p')
			options_list |= HASH_P_OPTION;
		else if (status == 'r')
			options_list |= HASH_R_OPTION;
		else if (status == 't')
			options_list |= HASH_T_OPTION;
		else if (status == e_invalid_input)
			return (status);
	}
	if (!args)
		return (e_invalid_input);
//ft_printf("et maintenant args pointe sur: %s\n", *args);
	if (check_for_needed_arguments(options_list, args))
		return (e_filename_arg_required);
//	ft_printf("pathname: %s\n", g_pathname);
	status = exec_hash_builtin(options_list, args);
	return (status > 0);
}

char	get_next_opt(char ***args)
{
	static int	x = 0;
	static char	options_list[] = "dlprt";

	x++;
	if (!args || !*args)
	{
		x = 0;
		return (-1);
	}
	if (!(**args)[x] && x > 0 && (**args)[x - 1] != 'p')
	{
		x = 1;
		*args += 1;
	}
	if (!(**args))
		return (get_next_opt(NULL));
	if ((**args)[0] == '-')
	{
		if ((**args)[x - 1] == 'p')
		{
			if (!(**args)[x] && !(*args)[1])
			{
				ft_dprintf(STDERR_FILENO, \
					"./21sh: hash: -p: option requires an argument\n");
				ft_dprintf(STDERR_FILENO, \
					"hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
				get_next_opt(NULL);
				return (e_invalid_input);
			}
			else if (!(**args)[x])
			{
				g_pathname = *(*args + 1);
				*args += 2;
			}
			else
			{
				g_pathname = **args + x;
				(*args)++;
			}
			return (get_next_opt(NULL));
		}
		if (x == 1 && (**args)[x] == '-' && !(**args)[x + 1])
		{
			(*args)++;
			return (get_next_opt(NULL));
		}
		if (ft_strchr(options_list, (**args)[x]))
			return ((**args)[x]);
		ft_dprintf(STDERR_FILENO, \
				"./21sh: hash: -%c: invalid option\n", (**args)[x]);
		ft_dprintf(STDERR_FILENO, \
				"hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
		get_next_opt(NULL);
		return (e_invalid_input);
	}
	return (get_next_opt(NULL));
}

int		check_for_needed_arguments(int options_list, char **args)
{
	if (!args)
		ft_printf("Huston nous avons un probleme je repete Huston nous avvvvvvvv....\n");
	if (!*args && options_list & HASH_T_OPTION)
	{
		ft_dprintf(STDERR_FILENO, \
				"./21sh: hash: -t: option requires an argument\n");
		return (e_invalid_input);
	}
	return (e_success);
}

int		contains_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (argv[i][1] == '-' && !argv[i][2])
		{
			i += 1;
			break ;
		}
		i++;
	}
	if (argv[i])
		return (i);
	return (0);
}

int		exec_hash_builtin(int options_list, char **args)
{
	int	status;

	status = e_success;
	if ((!*args && !(options_list & HASH_R_OPTION)) \
			|| (*args && !(*args + 1) && options_list & HASH_P_OPTION))
		return (print_hashed_commands(options_list));
	if (options_list & HASH_R_OPTION)
		del_hashed_commands();
	if (options_list & HASH_T_OPTION)
		return (print_hashed_targets(options_list, args));
	while (status != e_cannot_allocate_memory && *args)
	{
		if (options_list & HASH_P_OPTION)
			status = change_hash_entry(g_pathname, *args);
		else if (options_list & HASH_D_OPTION)
			remove_hash_entry(*args);
		else if ((*args)[0] != '.')
			status = add_name_hash_table(*args, 0);
		if (status == e_command_not_found || (*args)[0] == '.')
			ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", *args);
		args++;
	}
	return (status);
}
