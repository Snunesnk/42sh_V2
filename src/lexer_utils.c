/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:51:43 by efischer          #+#    #+#             */
/*   Updated: 2020/02/12 10:54:22 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			ft_ismeta(int c)
{
	int		ret;

	ret = FALSE;
	if (c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
		|| c == '<' || c == '>')
	{
		ret = TRUE;
	}
	return (ret);
}

char	*ft_join_free(char *s1, char *s2, int op)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (op == 1)
		ft_strdel(&s1);
	else if (op == 2)
		ft_strdel(&s2);
	else
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (str);
}

int		ft_is_space_tab(int c)
{
	int		ret;

	ret = FALSE;
	if (c == ' ' || c == '\t')
		ret = TRUE;
	return (ret);
}
