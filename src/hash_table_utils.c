/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:37:21 by snunes            #+#    #+#             */
/*   Updated: 2020/05/20 18:27:43 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "error.h"

t_hash_table	*find_occurence(char *name)
{
	t_hash_table	*tmp;
	int				hash;

	if (is_new_path())
		free_hash_table();
	hash = ft_hash(name);
	tmp = g_hash_table[hash];
	if (!tmp)
		return (NULL);
	while (tmp && !ft_strequ(tmp->command_name, name))
		tmp = tmp->next;
	return (tmp);
}

t_hash_table	*find_prev_occurence(char *name)
{
	t_hash_table	*tmp;
	t_hash_table	*prev;
	int				hash;

	prev = NULL;
	hash = ft_hash(name);
	tmp = g_hash_table[hash];
	if (!tmp)
		return (NULL);
	while (tmp && !ft_strequ(tmp->command_name, name))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
}

void			free_hash_table(void)
{
	t_hash_table	*next;
	t_hash_table	*tmp;
	unsigned int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		tmp = g_hash_table[i];
		while (tmp)
		{
			next = tmp->next;
			free(tmp->command_name);
			free(tmp->command_path);
			free(tmp);
			tmp = next;
		}
		g_hash_table[i] = NULL;
		i++;
	}
}

void			init_hash_table(void)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		g_hash_table[i] = NULL;
		i++;
	}
}

void			test_hash_path(void)
{
	static char	*path_remember = NULL;

	if (!path_remember)
		path_remember = getenv("PATH");
	else if (path_remember != getenv("PATH"))
	{
		free_hash_table();
		path_remember = getenv("PATH");
	}
}
