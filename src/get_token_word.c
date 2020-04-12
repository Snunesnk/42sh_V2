/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 12:05:43 by efischer          #+#    #+#             */
/*   Updated: 2020/04/12 20:03:27 by abarthel         ###   ########.fr       */
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
		while (ft_isdigit(str[i]) == TRUE)
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
	char	*tmp;

	len = 0;
	while (ft_isdigit(str[len]) == TRUE)
		len++;
	token->type = IO_NB;
	tmp = ft_strndup(str, len);
	token->value = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (token->value == NULL)
		len = 0;
	return (len);
}

static void		get_token_word(const char *str, t_token *token, size_t *len)
{
	char	*tmp;

	tmp = NULL;
	while (str[*len] != '\0' && ft_isblank(str[*len]) == FALSE
		&& ft_ismeta(str[*len]) == FALSE && str[*len] != '\n')
		if (str[*len] != '\0')
			(*len)++;
	tmp = ft_strndup(str, *len);
	token->value = ft_strdup(tmp);
	token->type = WORD;
	ft_strdel(&tmp);
	if (token->value == NULL)
		*len = 0;
}

size_t			get_word(const char *str, t_token *token,
					enum e_token *last_token_type)
{
	size_t	len;

	len = 0;
	if (str[len] == '#')
		len = get_token_comment(str, token);
	else if (str[len] == '-' && (*last_token_type == GREATAND
			|| *last_token_type == LESSAND || *last_token_type == ANDGREAT))
	{
		token->value = ft_strdup("-");
		token->type = WORD;
		len = 1;
	}
	else if (ft_isdigit(str[len]) == TRUE && is_io_number(str) == TRUE)
		len = get_token_ionumber(str, token);
	else
		get_token_word(str, token, &len);
	return (len);
}
