/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:52:47 by efischer          #+#    #+#             */
/*   Updated: 2020/04/15 22:33:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*is_valid_assignment(const char *str)
{
	char	*equal;

	if (!(equal = ft_strchr(str, '=')) || equal == str)
		return (NULL);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		++str;
	return (str == equal ? equal : NULL);
}

int		only_assignments(t_process *p)
{
	int i;

	i = 0;
	while (i < p->argc && is_valid_assignment(p->argv[i]))
		++i;
	return (i > 0 && i == p->argc);
}
