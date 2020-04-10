/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int	dollar_expansions(size_t *index, char **str, const char *opentag,
		const char *closetag)
{
	struct s_param_exp	exp;

	exp.lopen = ft_strlen(opentag);
	exp.lvarname = ft_varlen(&(*str)[exp.lopen], closetag);
	exp.lclose = ft_strlen(closetag);
	exp.rest = &(*str)[exp.lopen + exp.lvarname + exp.lclose];
	exp.lrest = ft_strlen(exp.rest);
	if ((exp.ret = getenv_content(&exp.content, &(*str)[exp.lopen],
					closetag)))
		return (exp.ret);
	exp.lcontent = ft_strlen(exp.content);
	if (!(exp.new = (char*)ft_memalloc(sizeof(char)
					* (exp.lrest + exp.lcontent + 1))))
	{
		ft_memdel((void**)&exp.content);
		return (e_cannot_allocate_memory);
	}
	if (exp.content)
		ft_strncat(exp.new, exp.content, exp.lcontent);
	ft_memdel((void**)&exp.content);
	ft_strncat(exp.new, exp.rest, exp.lrest);
	*str = exp.new;
	*index = exp.lcontent;
	return (e_success);
}
