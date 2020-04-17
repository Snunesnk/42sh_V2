/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/17 12:02:24 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*is_valid_assignment(const char *str)
{
	char	*equal;

	if (!str || !(equal = ft_strchr(str, '=')) || equal == str)
		return (NULL);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		++str;
	return (str == equal ? equal : NULL);
}

int		get_assignment(const char *assignment, char **name, char **value)
{
	*name = (char *)assignment;
	*value = NULL;
	if (!(*value = is_valid_assignment(assignment)))
		return (FAILURE);
	return (SUCCESS);
}

int		only_assignments(t_process *p)
{
	int i;

	i = 0;
	while (is_valid_assignment(p->argv[i]))
		++i;
	return (i > 0 && i == p->argc);
}
