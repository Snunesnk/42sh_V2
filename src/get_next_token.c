/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:01:46 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 12:01:48 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

static int		is_io_number(const char *str)
{
	size_t	i;

	i = 0;
	if (ft_atoifd(str) < 0)
		return (0);
	while (ft_isdigit(str[i]))
		++i;
	return (str[i] == '>' || str[i] == '<');
}

static t_token	*get_token_ionumber(const char *str, size_t *i)
{
	t_token	*token;
	int		len;

	len = 0;
	token = ft_memalloc(sizeof(t_token));
	while (ft_isdigit(str[*i + len]))
		++len;
	token->type = IO_NB;
	token->value = ft_strndup(&str[*i], len);
	*i += len;
	return (token);
}

static t_token	*get_token_word(const char *str, size_t *i, int prevtype)
{
	t_token	*token;
	int		qmode;
	int		len;

	len = 0;
	token = ft_memalloc(sizeof(t_token));
	if (str[*i] == '-' && (prevtype == GREATAND || prevtype == LESSAND))
		len += 1;
	else
	{
		qmode = NO_QUOTE;
		while (str[*i + len] && (qmode || (!ft_isblank(str[*i + len])
			&& !ft_ismeta(str[*i + len]) && str[*i + len] != '\n')))
		{
			qmode = get_qmode(qmode, str[*i + len]);
			++len;
		}
	}
	token->value = ft_strndup(&str[*i], len);
	token->type = WORD;
	*i += len;
	return (token);
}

t_token		*get_word(const char *str, size_t *i, int prevtype)
{
	t_token	*token;

	if (str[*i] == '#')
		while (str[*i] && str[*i] != '\n')
			++*i;
	if (ft_isdigit(str[*i]) && is_io_number(&str[*i]))
		token = get_token_ionumber(str, i);
	else
		token = get_token_word(str, i, prevtype);
	return (token);
}
