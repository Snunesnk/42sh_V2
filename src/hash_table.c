/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:01:22 by snunes            #+#    #+#             */
/*   Updated: 2020/05/15 20:17:45 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

t_hash_table	*(g_hash_table[HASH_SIZE]);

int				ft_hash(char *to_hash)
{
	unsigned int	key;
	int				x;

	key = FNV_OFFSET;
	x = 0;
	while (to_hash[x])
	{
		key *= FNV_PRIME;
		key ^= to_hash[x];
		x++;
	}
	key = key & (HASH_SIZE - 1);
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

int				add_to_hash_table(char *pathname, char *command_name, int nb)
{
	t_hash_table	*hash_ptr;
	t_hash_table	*prev;

	hash_ptr = find_occurence(command_name);
	if (!hash_ptr)
	{
		prev = find_prev_occurence(command_name);
		if (prev)
		{
			if (!(new_hash_entry(pathname, command_name, nb)))
				return (e_cannot_allocate_memory);
			return (0);
		}
		if (!(new_hash_entry(pathname, command_name, nb)))
			return (e_cannot_allocate_memory);
		return (0);
	}
	if (ft_strequ(hash_ptr->command_name, command_name))
	{
		hash_ptr->nb_called += nb;
		return (-1);
	}
	return (0);
}

int				add_name_hash_table(char *name, int nb)
{
	char	*pathname;
	int		status;

	if (!name || !*name)
		return (e_command_not_found);
	if (is_a_builtin(name))
		return (e_command_not_found);
	status = e_success;
	pathname = ft_strdup(name);
	status = path_concat(&pathname, NULL, NULL, NULL);
	if (status != e_command_not_found)
		add_to_hash_table(pathname, name, nb);
	free(pathname);
	return (status);
}

t_hash_table	*new_hash_entry(char *pathname, char *command_name, int nb)
{
	t_hash_table	*new_entry;
	int				hash;

	hash = ft_hash(command_name);
	if (!(new_entry = ft_memalloc(sizeof(*new_entry) * 1)))
		return (NULL);
	new_entry->next = g_hash_table[hash];
	g_hash_table[hash] = new_entry;
	if (!(new_entry->command_name = ft_strdup(command_name)))
		return (NULL);
	if (!(new_entry->command_path = ft_strdup(pathname)))
		return (NULL);
	new_entry->nb_called = nb;
	return (new_entry);
}
