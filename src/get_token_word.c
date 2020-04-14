/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 12:05:43 by efischer          #+#    #+#             */
/*   Updated: 2020/04/14 12:43:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int		is_io_number(const char *str)
{
	size_t	i;

	i = 0;
	if (ft_atoifd(str) < 0)
		return (FALSE);
	else
	{
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == '>' || str[i] == '<')
			return (TRUE);
	}
	return (FALSE);
}

static size_t	get_token_comment(const char *str, t_token *token)
{
	size_t	len;

	len = 0;
	token->type = COMMENT;
	token->value = ft_strdup(str);
	if (token->value != NULL)
		len = ft_strlen(token->value);
	return (len);
}

static size_t	get_token_ionumber(const char *str, t_token *token)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(str[len]))
		++len;
	token->type = IO_NB;
	token->value = ft_strndup(str, len);
	if (token->value == NULL)
		len = 0;
	return (len);
}

static void		get_token_word(const char *str, t_token *token, size_t *len)
{
	if (str[*len] == '-' && (token->type == GREATAND || token->type == LESSAND))
		*len = 1;
	else
		while (str[*len] && !ft_isblank(str[*len])
			&& !ft_ismeta(str[*len]) && str[*len] != '\n')
			++(*len);
	token->value = ft_strndup(str, *len);
	token->type = WORD;
	if (token->value == NULL)
		*len = 0;
}

size_t			get_word(const char *str, t_token *token)
{
	size_t	len;

	len = 0;
	if (str[len] == '#')
		len = get_token_comment(str, token);
	else if (ft_isdigit(str[len]) && is_io_number(str))
		len = get_token_ionumber(str, token);
	else
		get_token_word(str, token, &len);
	return (len);
}
