/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 21:41:45 by snunes            #+#    #+#             */
/*   Updated: 2020/05/14 14:15:57 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		has_no_cmd(char *line, int start)
{
	int	i;
	int	k;

	k = 0;
	i = start;
	while (i >= 0)
	{
		if (i >= 0 && ft_isspace(line[i]))
			i--;
		else if (i >= 0)
		{
			k = i;
			while (k > 0 && !ft_isspace(line[k]))
				k--;
			while (i > k)
			{
				if (line[i] == '=')
					i = k;
				i--;
			}
			if (k == i)
				return (0);
		}
	}
	return (1);
}

int		has_operator(char *to_complete)
{
	static char	operator[] = "&|<>;";
	int			i;

	i = 0;
	while (to_complete[i])
	{
		if (ft_strchr(operator, to_complete[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*new_str;

	if (!(new_str = ft_strjoin(s1, s2)))
		return (NULL);
	if (to_free & 1)
		free(s1);
	if (to_free & 2)
		free(s2);
	return (new_str);
}

int	stop_cmd(char c)
{
	static char	operator[] = "&|;<>";

	if (ft_strchr(operator, c) || ft_isspace(c))
		return (1);
	return (0);
}
