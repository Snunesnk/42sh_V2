/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:57 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/19 15:18:46 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		ft_ismeta(int c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

char	*ft_join_free(char *s1, char *s2, int op)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (op == 1)
		free(s1);
	else if (op == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (str);
}
