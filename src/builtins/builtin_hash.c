/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:06:23 by snunes            #+#    #+#             */
/*   Updated: 2020/02/26 22:44:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int		cmd_hash(int argc, char **argv)
{
	int		options_list;
	int		status;

	options_list = 0;
	while (argv && argc > 1 && (status = get_next_opt(argv)) != -1)
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
	if (check_for_needed_arguments(options_list, argc))
		return (e_filename_arg_required);
	status = exec_hash_builtin(options_list, argc, argv);
	return (status);
}

char	get_next_opt(char **argv)
{
	static int	x = 0;
	static int	y = 1;
	static char	options_list[] = "dlprt";

	x++;
	if (!argv[y][x])
	{
		x = 1;
		y += 1;
	}
	if (!argv[y])
	{
		x = 0;
		y = 1;
		return (-1);
	}
	if (argv[y][0] == '-')
	{
		if (x == 1 && argv[y][x] == '-' && !argv[y][x + 1])
		{
			x = 0;
			y = 1;
			return (-1);
		}
		if (ft_strchr(options_list, argv[y][x]))
			return (argv[y][x]);
		else
		{
			ft_printf("./21sh: hash: -%c: invalid option", argv[y][x]);
			return (e_invalid_input);
		}
	}
	x = 0;
	y = 1;
	return (-1);
}

int		check_for_needed_arguments(int options_list, int argc)
{
	if ((options_list & HASH_T_OPTION || options_list & HASH_P_OPTION) \
			&& argc < 3)
	{
		if (options_list & HASH_T_OPTION)
			ft_printf("./21sh: hash: -t: option requires an argument\n");
		else
			ft_printf("./21sh: hash: -p: option requires an argument\n");
		ft_printf("hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
		return (e_invalid_input);
	}
	return (0);
}

int		exec_hash_builtin(int options_list, int argc, char **argv)
{
	int	i;
	int	status;

	i = (argv[1] && argv[1][0] == '-') ? 2 : 1;
	status = e_success;
	if (((!argv || argc < 2 || (argc == 2 && argv[1][0] == '-'))\
				&& !(options_list & HASH_R_OPTION)) \
			|| ((options_list & HASH_P_OPTION) && argc < 4))
		return (print_hashed_commands(options_list));
	if (options_list & HASH_R_OPTION)
		del_hashed_commands();
	if (options_list & HASH_T_OPTION || options_list & HASH_L_OPTION)
		return (print_hashed_targets(options_list, argv));
	while (status == e_success && argv[i])
	{
		if (options_list & HASH_P_OPTION && i != 2)
			status = change_hash_entry(argv[2], argv[i]);
		else if (options_list & HASH_D_OPTION)
			remove_hash_entry(argv[i]);
		else if (add_name_hash_table(argv[i]))
			status = e_cannot_allocate_memory;
		i++;
	}
	return (e_success);
}
