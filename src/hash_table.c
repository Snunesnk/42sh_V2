/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:01:22 by snunes            #+#    #+#             */
/*   Updated: 2020/02/26 22:44:25 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_hash_table	**g_hash_table;

int				ft_hash(char *to_hash)
{
	int	key;
	int	x;

	key = 0;
	x = 0;
	while (to_hash[x])
	{
		key += to_hash[x] * x;
		x++;
	}
	key = key % HASH_SIZE;
	return (key);
}

int				check_hash_table(char *command_name)
{
	int	hash;

	hash = ft_hash(command_name);
	if (!g_hash_table[hash])
		return (e_command_not_found);
	else
		return (e_success);
}

int				add_to_hash_table(char *pathname, char *command_name)
{
	t_hash_table	**hash_ptr;
	t_hash_table	*hash_ptr_save;
	int				hash;

	hash = ft_hash(command_name);
	hash_ptr = &(g_hash_table[hash]);
	hash_ptr_save = g_hash_table[hash];
	if (g_hash_table[hash])
	{
		while (*hash_ptr && !ft_strequ((*hash_ptr)->command_name, command_name))
			*hash_ptr = (*hash_ptr)->next;
		if (*hash_ptr && ft_strequ((*hash_ptr)->command_name, command_name))
		{
			(*hash_ptr)->nb_called += 1;
			return (0);
		}
	}
	if (!(*hash_ptr = new_hash_entry(pathname, command_name)))
		return (1);
	return (0);
}

int				add_name_hash_table(char *name)
{
	char	*pathname;
	int		status;

	status = e_success;
	pathname = ft_strdup(name);
	status = path_concat(&pathname);
	if (status != e_command_not_found)
		add_to_hash_table(pathname, name);
	free(pathname);
	if (status != e_command_not_found)
		g_hash_table[ft_hash(name)]->nb_called = 0;
	return (status);
}

t_hash_table	*new_hash_entry(char *pathname, char *command_name)
{
	t_hash_table	*new_entry;

	if (!(new_entry = ft_memalloc(sizeof(*new_entry) * 1)))
		return (NULL);
	new_entry->next = NULL;
	if (!(new_entry->command_name = ft_strdup(command_name)))
		return (NULL);
	if (!(new_entry->command_path = ft_strdup(pathname)))
		return (NULL);
	new_entry->nb_called = 1;
	return (new_entry);
}
