/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:00:17 by snunes            #+#    #+#             */
/*   Updated: 2020/03/06 21:14:21 by snunes           ###   ########.fr       */
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
	if (!nb)
		ft_printf("hash: hash table empty\n");
	return (0);
}

void	del_hashed_commands(void)
{
	unsigned int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (g_hash_table[i])
		{
			free(g_hash_table[i]->command_path);
			free(g_hash_table[i]->command_name);
			free(g_hash_table[i]);
			g_hash_table[i] = NULL;
		}
		i++;
	}
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
			ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", *args);
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

	status = e_success;
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: Is a directory\n", path);
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
		ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", name);
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
