/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:00:17 by snunes            #+#    #+#             */
/*   Updated: 2020/05/15 13:04:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int		print_hashed_commands(int options_list)
{
	t_hash_table	*tmp;
	unsigned int	i;
	int				nb;

	nb = 0;
	i = 0;
	while (i < HASH_SIZE)
	{
		if (g_hash_table[i])
		{
			tmp = g_hash_table[i];
			nb++;
			if (nb == 1 && !(options_list & HASH_L_OPTION))
				ft_printf("hits\tcommand\n");
			print_hashed_commands_util(tmp, options_list & HASH_L_OPTION);
		}
		i++;
	}
	return (0);
}

int		print_hashed_targets(int options_list, char **args)
{
	t_hash_table	*tmp;
	int				status;
	int				multiple;

	multiple = 0;
	status = e_success;
	if (!(options_list & HASH_T_OPTION) && *args)
		return (print_hashed_commands(options_list));
	if (*args && args[1])
		multiple = 1;
	while (*args)
	{
		if (!(tmp = find_occurence(*args)))
		{
			pbierror("%s: not found", *args);
			status = e_command_not_found;
		}
		else
		{
			print_hashed_targets_util(tmp, (options_list & HASH_L_OPTION), \
					*args, multiple);
		}
		args++;
	}
	return (status);
}

int		change_hash_entry(char *path, char *name)
{
	struct stat		path_stat;
	int				status;

	ft_bzero(&path_stat, sizeof(struct stat));
	status = e_success;
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		pbierror("%s: Is a directory", path);
		return (e_invalid_input);
	}
	if (find_occurence(name))
		remove_hash_entry(name);
	status = add_to_hash_table(path, name, 0);
	return (status);
}

void	remove_hash_entry(char *name)
{
	t_hash_table	*tmp;
	t_hash_table	*prev;
	int				hash;

	hash = ft_hash(name);
	tmp = find_occurence(name);
	if (!tmp)
	{
		pbierror("%s: not found", name);
		return ;
	}
	prev = find_prev_occurence(name);
	free(tmp->command_path);
	free(tmp->command_name);
	if (prev)
		prev->next = tmp->next;
	else
		g_hash_table[hash] = tmp->next;
	free(tmp);
}
