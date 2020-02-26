/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:00:17 by snunes            #+#    #+#             */
/*   Updated: 2020/02/26 22:44:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int		print_hashed_commands(int options_list)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (i < HASH_SIZE)
	{
		if (g_hash_table[i])
		{
			nb++;
			if (!(options_list & HASH_L_OPTION))
			{
				if (nb == 1)
					ft_printf("hits\tcommand\n");
				ft_printf("%4d\t%s\n", g_hash_table[i]->nb_called, \
						g_hash_table[i]->command_path);
			}
			else
				ft_printf("builtin hash -p %s %s\n", \
						g_hash_table[i]->command_path, \
						g_hash_table[i]->command_name);
		}
		i++;
	}
	if (!nb)
		ft_printf("hash: hash table empty\n");
	return (0);
}

void	del_hashed_commands(void)
{
	int	i;

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
	int	i;
	int	status;
	int	multiple;

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
		if (!g_hash_table[ft_hash(argv[i])])
		{
			status = e_invalid_input;
			ft_printf("./21sh: hash: %s: not found\n", argv[i]);
		}
		else
		{
			if (options_list & HASH_L_OPTION)
				ft_printf("builtin hash -p %s %s\n", \
						g_hash_table[ft_hash(argv[i])]->command_path, argv[i]);
			else
			{
				if (multiple)
					ft_printf("%s\t", argv[i]);
				ft_printf("%s\n", g_hash_table[ft_hash(argv[i])]->command_path);
			}
		}
		i++;
	}
	return (status);
}

int		change_hash_entry(char *pathname, char *name)
{
	int			hash;
	struct stat	path_stat;

	stat(pathname, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		ft_printf("./21sh: hash: %s: Is a directory\n", pathname);
		return (e_invalid_input);
	}
	hash = ft_hash(name);
	if (!g_hash_table[hash])
	{
		if (add_to_hash_table(pathname, name) == e_cannot_allocate_memory)
			return (e_cannot_allocate_memory);
		return (e_success);
	}
	free(g_hash_table[hash]->command_path);
	if (!(g_hash_table[hash]->command_path = ft_strdup(pathname)))
		return (e_cannot_allocate_memory);
	return (e_success);
}

void	remove_hash_entry(char *name)
{
	int	hash;

	hash = ft_hash(name);
	if (!g_hash_table[hash])
	{
		ft_printf("./21sh: hash: %s: not found\n", name);
		return ;
	}
	free(g_hash_table[hash]->command_path);
	free(g_hash_table[hash]->command_name);
	free(g_hash_table[hash]);
	g_hash_table[hash] = NULL;
}
