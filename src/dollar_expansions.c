/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 15:36:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	get_new_str(char **str, char **content, char *rest)
{
	char	*new;
	size_t	lcontent;
	int		lrest;

	lrest = ft_strlen(rest);
	lcontent = ft_strlen(*content);
	if (!(new = (char*)ft_memalloc(sizeof(char) * (lrest + *lcontent + 1))))
	{
		ft_memdel((void**)&content);
		return (e_cannot_allocate_memory);
	}
	if (content)
		ft_strncat(new, *content, lcontent);
	ft_memdel((void**)content);
	ft_strncat(new, rest, lrest);
	*str = new;
	return (e_success);
}

int			dollar_expansions(size_t *lcontent, char **str, \
		const char *opentag, const char *closetag)
{
	int		ret;
	size_t	lopen;
	size_t	lclose;
	char	*content;
	char	*rest;

	lopen = ft_strlen(opentag);
	lclose = ft_strlen(closetag);
	rest = &(*str)[lopen + ft_varlen(&(*str)[lopen], closetag) + lclose];
	if ((ret = getenv_content(&content, &(*str)[lopen], closetag)))
		return (ret);
	*lcontent = ft_strlen(content);
	if (get_new_str(str, &content, rest))
		return (e_cannot_allocate_memory);
	return (e_success);
}
