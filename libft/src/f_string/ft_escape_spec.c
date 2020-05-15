/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:32:57 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/15 16:57:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_spec(const char *str, const char *spec)
{
	int	nb_spec;

	nb_spec = 0;
	while (*str)
		nb_spec += !!ft_strchr(spec, *str++);
	return (nb_spec);
}

char	*ft_escape_spec(const char *str, const char *spec)
{
	char	*ptr;
	char	*dup;
	int		nb;

	if (!str || !spec)
		return (NULL);
	if (!(nb = count_spec(str, spec)))
		return (ft_strdup(str));
	if (!(dup = ft_strnew(nb + ft_strlen(str) + 1)))
		return (NULL);
	ptr = dup;
	while (*str)
	{
		if (ft_strchr(spec, *str))
			*ptr++ = '\\';
		*ptr++ = *str++;
	}
	*ptr = '\0';
	return (dup);
}
