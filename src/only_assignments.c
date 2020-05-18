/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/17 18:23:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		is_valid_identifier(const char *str, const char *stop)
{
	if (!str || !*str)
		return (0);
	while (*str && str != stop && (*str == '_' || ft_isalnum(*str)))
		++str;
	return (stop ? str == stop : !*str);
}

char	*is_valid_assignment(const char *str)
{
	char	*equal;

	if (!str || !(equal = ft_strchr(str, '=')) || equal == str)
		return (NULL);
	return (is_valid_identifier(str, equal) ? equal : NULL);
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
