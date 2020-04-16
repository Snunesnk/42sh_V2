/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 13:55:07 by abarthel         ###   ########.fr       */
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
