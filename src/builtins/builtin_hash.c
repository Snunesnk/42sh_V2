/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:06:23 by snunes            #+#    #+#             */
/*   Updated: 2020/02/27 18:17:20 by snunes           ###   ########.fr       */
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
	if (check_for_needed_arguments(options_list, argc, argv))
		return (e_filename_arg_required);
	status = exec_hash_builtin(options_list, argv);
	return (status > 0);
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

int		check_for_needed_arguments(int options_list, int argc, char **argv)
{
	if ((options_list & HASH_T_OPTION && contains_arg(argv) < 1))
	{
		ft_printf("./21sh: hash: -t: option requires an argument\n");
		return (e_invalid_input);
	}
	else if (options_list & HASH_T_OPTION && argc < 3)
	{
		ft_printf("./21sh: hash: -p: option requires an argument\n");
		ft_printf("hash: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n");
		return (e_invalid_input);
	}
	return (e_success);
}

int		contains_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
		i++;
	if (argv[i])
		return (i);
	return (0);
}

int		exec_hash_builtin(int options_list, char **argv)
{
	int	i;
	int	status;

	i = (argv[1] && argv[1][0] == '-') ? 2 : 1;
	status = e_success;
	if (!contains_arg(argv) && !(options_list & HASH_R_OPTION))
		return (print_hashed_commands(options_list));
	if (options_list & HASH_R_OPTION)
		del_hashed_commands();
	if (options_list & HASH_T_OPTION)
		return (print_hashed_targets(options_list, argv));
	while (status != e_cannot_allocate_memory && argv[i])
	{
		if (options_list & HASH_P_OPTION && i != 2)
			status = change_hash_entry(argv[2], argv[i]);
		else if (options_list & HASH_D_OPTION && !(options_list & HASH_P_OPTION)\
				&& i >= contains_arg(argv))
			remove_hash_entry(argv[i]);
		else if (options_list == 0)
			status = add_name_hash_table(argv[i], 0);
		if (status == e_command_not_found)
			ft_printf("./21sh: hash: %s: not found\n", argv[i]);
		i++;
	}
	return (status);
}
