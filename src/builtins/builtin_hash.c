/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:06:23 by snunes            #+#    #+#             */
/*   Updated: 2020/02/28 15:30:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int		cmd_hash(int argc, char **argv)
{
	char	**args;
	int		options_list;
	int		status;

	if (argv)
		args = argv + 1;
	else
		args = argv;
	ft_printf("args pointe sur: %s\n", *args);
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
	ft_printf("et maintenant args pointe sur: %s\n", *args);
	if (check_for_needed_arguments(options_list, argc, argv))
		return (e_filename_arg_required);
	status = exec_hash_builtin(options_list, argc, argv);
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
			if (!(**args)[x] && !contains_arg(*args))
			{
				ft_dprintf(STDERR_FILENO, \
					"./21sh: hash: -p: option requires an argument\n");
				ft_dprintf(STDERR_FILENO, \
					"hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
				get_next_opt(NULL);
				return (e_invalid_input);
			}
			else
			{
				ft_printf("passage de %s a , x: %d", **args, x);
				ft_memmove(**args, **args + x, ft_strlen(**args - x));
				ft_printf("%s\n", **args);
			}
			return (get_next_opt(NULL));
		}
		if (x == 1 && (**args)[x] == '-' && !(**args)[x + 1])
			return (get_next_opt(NULL));
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

int		check_for_needed_arguments(int options_list, int argc, char **argv)
{
	(void)argc;
	if (contains_arg(argv) < 1 && options_list & HASH_T_OPTION)
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

int		exec_hash_builtin(int options_list, int argc, char **argv)
{
	int	i;
	int	status;

	i = (argv[1] && argv[1][0] == '-') ? 2 : 1;
	status = e_success;
	if ((!contains_arg(argv) && !(options_list & HASH_R_OPTION)) \
			|| (argc - contains_arg(argv) == 1 && options_list & HASH_P_OPTION))
		return (print_hashed_commands(options_list));
	if (options_list & HASH_R_OPTION)
		del_hashed_commands();
	if (options_list & HASH_T_OPTION)
		return (print_hashed_targets(options_list, argv));
	while (status != e_cannot_allocate_memory && argv[i])
	{
		if (options_list & HASH_P_OPTION && i > contains_arg(argv))
			status = change_hash_entry(argv[contains_arg(argv)], argv[i]);
		else if (options_list & HASH_D_OPTION && !(options_list & HASH_P_OPTION)\
				&& i >= contains_arg(argv))
			remove_hash_entry(argv[i]);
		else if (!(options_list & HASH_P_OPTION) \
				&& !(options_list & HASH_D_OPTION) \
				&& argv[i][0] != '.')
			status = add_name_hash_table(argv[i], 0);
		if (status == e_command_not_found || argv[i][0] == '.')
			ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", argv[i]);
		i++;
	}
	return (status);
}
