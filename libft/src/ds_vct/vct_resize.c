/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:23:20 by efischer          #+#    #+#             */
/*   Updated: 2019/10/29 15:05:56 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"vctlib.h"

static char	*get_content(t_vector *vct)
{
	size_t		overflow;
	size_t		align;
	char		*content;

	overflow = vct->len - vct->size;
	align = overflow - overflow % DFL_SCALE;
	vct->scale = 2 * align;
	vct->size += vct->scale;
	content = ft_strdup(vct->str);
	ft_strdel(&(vct->str));
	return (content);
}

int			vct_resize(t_vector	*vct)
{
	char		*content;
	size_t		len;
	int			ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
	{
		content = get_content(vct);
		if (content == NULL)
			ret = FAILURE;
		else
		{
			len = ft_strlen(content);
			vct->str = (char*)malloc(sizeof(char) * vct->size);
			ft_bzero(vct->str, vct->size);
			if (vct->str != NULL)
				vct->str = (char*)ft_memmove(vct->str, content, len);
			else
				ret = FAILURE;
			ft_strdel(&content);
		}
	}
	return (ret);
}
