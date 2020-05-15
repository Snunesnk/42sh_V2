/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:44:09 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/15 13:50:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

#define IFS	"\t \n"

static int	unquoted_ifs(char const *ifs, char c, int *qmode)
{
	*qmode = get_qmode(*qmode, c);
	return (*qmode == NO_QUOTE && ft_strchr(ifs, c));
}

static char	**ft_strplit_ifs(char const *s, char const *ifs)
{
	static int	i = 0;
	int			qmode;
	int			l;
	char		*cpy;
	char		**tb;

	qmode = NO_QUOTE;
	tb = NULL;
	cpy = NULL;
	i = i == -1 ? 1 : i + 1;
	while (*s && unquoted_ifs(ifs, *s, &qmode))
		++s;
	l = *s ? 1 : 0;
	while (s[l] && !unquoted_ifs(ifs, s[l], &qmode))
		++l;
	if (l && !(cpy = ft_strndup(s, l)))
		i = -1;
	if (i != -1 && !(tb = cpy ? ft_strplit_ifs(s + l, ifs)
		: (char **)ft_memalloc(i * sizeof(char *))))
		i = -1;
	if (i == -1 && cpy)
		free(cpy);
	else if (i != -1)
		tb[--i] = cpy;
	return (tb);
}

int			field_split(t_process *p, int i, int *fields)
{
	int		ret;
	char	**new_fields;

	if (!has_unquoted_spec_chars(p->argv[i], IFS))
		return (0);
	if (!(new_fields = ft_strplit_ifs(p->argv[i], IFS)))
		return (e_cannot_allocate_memory);
	*fields = (int)ft_tablen(new_fields);
	ret = replace_fields(p, i, new_fields, *fields);
	ft_tabdel(&new_fields);
	return (ret);
}
