/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 09:57:43 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/19 09:57:45 by yforeau          ###   ########.fr       */
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
