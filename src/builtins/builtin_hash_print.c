/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:00:17 by snunes            #+#    #+#             */
/*   Updated: 2020/02/28 15:30:06 by snunes           ###   ########.fr       */
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
			if (!(options_list & HASH_L_OPTION))
			{
				if (nb == 1)
					ft_printf("hits\tcommand\n");
				while (tmp)
				{
					ft_printf("%4d\t%s\n", tmp->nb_called, tmp->command_path);
					tmp = tmp->next;
				}
			}
			else if (options_list == HASH_L_OPTION)
			{
				while (tmp)
				{
					ft_printf("builtin hash -p %s %s\n", tmp->command_path, \
						tmp->command_name);
					tmp = tmp->next;
				}
			}
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
			/* Iterer sur l'entry pour voir si il n'y a pas plusieurs choses stockees*/
			free(g_hash_table[i]->command_path);
			free(g_hash_table[i]->command_name);
			free(g_hash_table[i]);
			g_hash_table[i] = NULL;
		}
		i++;
	}
}
int		print_hashed_targets(int options_list, char **argv)
{
	t_hash_table	*tmp;
	int				i;
	int				status;
	int				multiple;

	multiple = 0;
	i = 1;
	status = e_success;
	while (argv[i] && argv[i][0] == '-')
		i++;
	if (!(options_list & HASH_T_OPTION) && argv[i])
		return (print_hashed_commands(options_list));
	if (argv[i] && argv[i + 1] && !(options_list & HASH_L_OPTION))
		multiple = 1;
	while (argv[i])
	{
		tmp = find_occurence(argv[i]);
		if (!tmp)
		{
			status = e_invalid_input;
			ft_dprintf(STDERR_FILENO, "./21sh: hash: %s: not found\n", argv[i]);
		}
		else
		{
			if (options_list & HASH_L_OPTION)
				ft_printf("builtin hash -p %s %s\n", tmp->command_path, argv[i]);
			else
			{
				if (multiple)
					ft_printf("%s\t", argv[i]);
				ft_printf("%s\n", tmp->command_path);
			}
		}
		i++;
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
